#ifndef DANDAN_CHANGECHARACTERISTICS_H
#define DANDAN_CHANGECHARACTERISTICS_H

#include "dandan/core/Card.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    class ChangeCharacteristicsEffect : public IOneShotEffect
    {

    public:
        ChangeCharacteristicsEffect(core::Target target,
                                    core::CardCharacteristics characteristics,
                                    EffectContext context)
            : IOneShotEffect(std::move(context)), m_target(std::move(target)),
              m_card_characteristics(std::move(characteristics))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<ChangeCharacteristicsEffect>(
                m_target, m_card_characteristics, getEffectContext());
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            [[maybe_unused]] core::ExecutionContext exec_ctx) const override;

    private:
        core::Target m_target;
        core::CardCharacteristics m_card_characteristics;
    };

    class ChangeCharacteristicsEffectDefinition
        : public IOneShotEffectDefinition
    {

    public:
        explicit ChangeCharacteristicsEffectDefinition(
            core::TargetRequirement target_reqs,
            core::CardCharacteristics characteristics)
            : m_target_requirements(std::move(target_reqs)),
              m_card_characteristics(std::move(characteristics))
        {
            std::cout << "Size of addditional abilities after construction: "
                      << m_card_characteristics.additional_abilities.size()
                      << '\n';
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            const core::ExecutionContext exec_ctx,
            EffectContext context) const override
        {
            auto &card_registry{exec_ctx.cards.get()};
            const auto *card{card_registry[context.card_id.value()]};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            context.expires = expires();
            return std::make_unique<ChangeCharacteristicsEffect>(
                choice, m_card_characteristics, context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<ChangeCharacteristicsEffectDefinition>(
                m_target_requirements, m_card_characteristics);
        }

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override
        {
            return &m_target_requirements;
        }

        [[nodiscard]] const core::CardCharacteristics &getCharacteristics()
            const
        {
            return m_card_characteristics;
        }

    private:
        core::TargetRequirement m_target_requirements;
        core::CardCharacteristics m_card_characteristics;
    };
} // namespace dandan::effects


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{

    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::abilities;
    using namespace dandan::core;

    inline const auto registeredChangeCharacteristicsEffect = []
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

#endif
