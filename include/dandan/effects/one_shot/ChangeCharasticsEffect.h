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
                                    EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

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
            core::CardCharacteristics characteristics);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            core::ExecutionContext exec_ctx,
            EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override;

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override;

        [[nodiscard]] const core::CardCharacteristics &getCharacteristics()
            const;

    private:
        core::TargetRequirement m_target_requirements;
        core::CardCharacteristics m_card_characteristics;
    };
} // namespace dandan::effects

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
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

                    for (const auto &ability :
                         characteristics.additional_abilities)
                    {

                        auto sub_json =
                            JsonFactory<IAbility>::create_json(ability.get());
                        characteristics_json["additional_abilities"].push_back(
                            sub_json);
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

                    const auto &color = characteristics_json["color"];
                    const auto &subtypes = characteristics_json["subtypes"];
                    const auto &base_power = characteristics_json["base_power"];
                    const auto &base_thoughness =
                        characteristics_json["base_thoughness"];
                    const auto &stats{Stats{base_power, base_thoughness}};
                    const auto &loses_all_abilities =
                        characteristics_json["loses_all_abilities"];

                    auto additional_abilities_json = characteristics_json.value(
                        "additional_abilities", nlohmann::json::array());

                    auto additional_abilities{
                        std::vector<std::unique_ptr<IAbility>>{},
                    };

                    for (const auto &ability_json : additional_abilities_json)
                    {
                        auto ability =
                            JsonFactory<IAbility>::create_product(ability_json);
                        additional_abilities.emplace_back(std::move(ability));
                    }

                    auto card_characteristics{CardCharacteristics{
                        color, subtypes, stats, loses_all_abilities,
                        std::move(additional_abilities)}};

                    auto effect{
                        std::make_unique<ChangeCharacteristicsEffectDefinition>(
                            TargetRequirement{target_specs},
                            card_characteristics)};

                    effect->addExpireTime(expiry);
                    return effect;
                });
        return true;
    }();
} // namespace dandan::serialization::registration
#endif

#endif
