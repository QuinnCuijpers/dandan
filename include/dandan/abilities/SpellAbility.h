#ifndef DANDAN_SPELL_ABILITY_H
#define DANDAN_SPELL_ABILITY_H

#include "dandan/abilities/IAbility.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>

namespace dandan::abilities
{
    /** @brief A spell ability that can have multiple effects.
     * @class SpellAbility
     *
     * @implements IAbility
     */
    class SpellAbility : public IAbility
    {
    public:
        /** @brief Construct a spell ability with the given effect definitions.
         * @param effects The vector of effect definitions for the spell
         * ability.
         */
        // TODO: change to take value instead of Rvalue
        explicit SpellAbility(
            std::vector<std::unique_ptr<effects::IOneShotEffectDefinition>>
                &&effects);

        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::ExecutionContext exec_ctx,
            AbilityContext context) const override;

        /** @brief Get the effect definitions of the spell ability.
         * @return The vector of effect definitions for the spell ability.
         */
        [[nodiscard]] const std::vector<
            std::unique_ptr<effects::IOneShotEffectDefinition>> &
        effects() const;

    private:
        std::vector<std::unique_ptr<effects::IOneShotEffectDefinition>>
            m_effects;
        std::optional<size_t> m_chosen_effect_index;
    };
} // namespace dandan::abilities


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization::registration
{

    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::effects;

    inline const auto registeredSpellAbility = []
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

#endif
