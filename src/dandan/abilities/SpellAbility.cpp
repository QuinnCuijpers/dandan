#include "dandan/abilities/SpellAbility.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/EffectList.h"
#include <iostream>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace
{

    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::effects;

    const auto registered = []
    {
        AbilityRegistry::instance().registerType<SpellAbility>(
            "SpellAbility",
            [](const IAbility *ability)
            {
                auto json = nlohmann::json::object();
                const auto *spell_ability{
                    dynamic_cast<const SpellAbility *>(ability)};
                auto effect_list = nlohmann::json::array();
                std::transform(
                    spell_ability->effects().begin(),
                    spell_ability->effects().end(),
                    std::back_inserter(effect_list),
                    [](const auto &effect)
                    {
                        return JsonFactory<IOneShotEffectDefinition>::
                            create_json(effect.get());
                    });

                json["effect_list"] = effect_list;
                return json;
            },
            [](const nlohmann::json &json)
            {
                std::vector<std::unique_ptr<IOneShotEffectDefinition>>
                    effect_list;
                std::transform(
                    json.at("effect_list").begin(),
                    json.at("effect_list").end(),
                    std::back_inserter(effect_list),
                    [](const auto &effect_json)
                    {
                        return JsonFactory<IOneShotEffectDefinition>::
                            create_product(effect_json);
                    });
                return std::make_unique<SpellAbility>(std::move(effect_list));
            });

        return true;
    }();
} // namespace
#endif

namespace dandan::abilities
{

    SpellAbility::SpellAbility(
        std::vector<std::unique_ptr<effects::IOneShotEffectDefinition>>
            &&effects)
        : m_effects(std::move(effects))
    {
    }

    std::unique_ptr<effects::IOneShotEffect> SpellAbility::createEffect(
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Creating spell effect with size: " << effects().size()
                  << "\n";
        if (effects().empty())
        {
            // TODO: consider returning a no-op effect instead of nullptr to
            // avoid null checks
            std::cout << "WARNING: No effects to create for spell ability\n";
            return nullptr;
        }

        auto bound_effects{
            std::vector<std::unique_ptr<effects::IOneShotEffect>>{}};
        effects::EffectContext effect_context{context.source_card_id,
                                              context.controller_id};
        for (const auto &effect_def : effects())
        {
            auto effect{effect_def->bind(game, effect_context)};
            bound_effects.push_back(std::move(effect));
        }
        return std::make_unique<effects::EffectList>(std::move(bound_effects),
                                                     effect_context);
    }

    [[nodiscard]] const std::vector<
        std::unique_ptr<effects::IOneShotEffectDefinition>> &
    SpellAbility::effects() const
    {
        return m_effects;
    }

} // namespace dandan::abilities
