#include "dandan/core/Battlefield.h"
#include "dandan/core/Expire.h"
#include "dandan/effects/one_shot/ChangeCharasticsEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <stdexcept>
#include <variant>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
#endif

#ifdef DANDAN_SERIALIZE
namespace
{

    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::abilities;
    using namespace dandan::core;

    const auto registered = []
    {
        OneShotEffectRegistry::instance()
            .registerType<ChangeCharacteristicsEffectDefinition>(
                "ChangeCharacteristicsEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *change_effect = dynamic_cast<
                        const ChangeCharacteristicsEffectDefinition *>(effect);
                    auto characteristics{change_effect->getCharacteristics()};
                    auto characteristics_json = nlohmann::json::object();
                    characteristics_json["color"] = characteristics.color;
                    characteristics_json["subtypes"] = characteristics.subtypes;
                    characteristics_json["base_power"] =
                        characteristics.base_stats.power;
                    characteristics_json["base_thoughness"] =
                        characteristics.base_stats.toughness;
                    characteristics_json["loses_all_abilities"] =
                        characteristics.loses_all_abilities;
                    characteristics_json["additional_keywords"] =
                        nlohmann::json::array();
                    for (const auto *ability :
                         characteristics.additional_abilities)
                    {
                        if (isFlyingAbility(*ability))
                        {
                            characteristics_json["additional_keywords"]
                                .push_back("Flying");
                        }
                        else
                        {
                            auto sub_json{
                                JsonFactory<IAbility>::create_json(ability)};
                            characteristics_json["additional_abilities"]
                                .push_back(sub_json);
                        }
                    }
                    json["characteristics"] = characteristics_json;
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   ExpireTime expiry)
                {
                    const auto &characteristics_json =
                        data.at("characteristics");

                    auto color = characteristics_json["color"];
                    auto subtypes = characteristics_json["subtypes"];
                    auto base_power = characteristics_json["base_power"];
                    auto base_thoughness =
                        characteristics_json["base_thoughness"];
                    auto stats{Stats{base_power, base_thoughness}};
                    auto loses_all_abilities =
                        characteristics_json["loses_all_abilities"];

                    auto additional_keywords_json =
                        characteristics_json["additional_keywords"];

                    auto additional_keywords{std::vector<Keyword>{}};

                    for (const auto &keyword : additional_keywords_json)
                    {
                        Keyword keyword_v = keyword;
                        additional_keywords.push_back(keyword_v);
                    }

                    auto additional_abilities{std::vector<const IAbility *>{}};

                    for (auto keyword : additional_keywords)
                    {
                        const auto *ability = getKeywordAbility(keyword);
                        additional_abilities.push_back(ability);
                    }

                    auto card_characteristics{CardCharacteristics{
                        color, subtypes, stats, loses_all_abilities,
                        additional_abilities}};

                    auto effect{
                        std::make_unique<ChangeCharacteristicsEffectDefinition>(
                            TargetRequirement{target_specs},
                            card_characteristics)};

                    effect->addExpireTime(expiry);
                    return effect;
                });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ChangeCharacteristicsEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        if (!std::holds_alternative<core::Permanent>(m_target))
        {
            throw std::runtime_error(
                "Target for ChangeCharacteristicsEffect was not a Permanent");
        }
        auto permanent_id{std::get<core::Permanent>(m_target)};
        auto *card{card_registry[permanent_id]};

        const auto &old_abilities{card->getCurrentAbilities()};
        auto old_characteristics{card->getCharacteristics()};
        for (const auto &ability : old_abilities)
        {
            old_characteristics.additional_abilities.push_back(
                &ability.definition());
        }

        card->setCharacteristics(m_card_characteristics, exec_ctx);
        card->setPrevCharacteristics(old_characteristics);

        if (auto expiry = getEffectContext().expires;
            expiry != core::ExpireTime::None)
        {
            if (expiry == core::ExpireTime::EnfOfTurn)
            {
                auto old_characistics{card->getPrevCharacteristics()};
                old_characteristics.loses_all_abilities = true;

                auto context{getEffectContext()};
                context.expires = core::ExpireTime::None;
                auto undo_effect{std::make_unique<ChangeCharacteristicsEffect>(
                    m_target, old_characteristics, context)};
                game.addEndOfTurnEffect(std::move(undo_effect));
            }
        }
        return nullptr;
    }
} // namespace dandan::effects
