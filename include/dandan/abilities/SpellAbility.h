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
        explicit SpellAbility(
            std::vector<std::unique_ptr<effects::IOneShotEffectDefinition>>
                &&effects)
            : m_effects(std::move(effects))
        {
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const override;

        /** @brief Get the effect definitions of the spell ability.
         * @return The vector of effect definitions for the spell ability.
         */
        [[nodiscard]] const std::vector<
            std::unique_ptr<effects::IOneShotEffectDefinition>> &
        effects() const
        {
            return m_effects;
        }

    private:
        std::vector<std::unique_ptr<effects::IOneShotEffectDefinition>>
            m_effects;
        std::optional<size_t> m_chosen_effect_index;
    };
} // namespace dandan::abilities

#endif