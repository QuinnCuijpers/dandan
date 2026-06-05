#ifndef DANDAN_SPELL_ABILITY_H
#define DANDAN_SPELL_ABILITY_H

#include "dandan/abilities/IAbility.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>

namespace dandan::abilities
{
    class SpellAbility : public IAbility
    {
    public:
        SpellAbility(
            std::vector<std::unique_ptr<effects::IOneShotEffect>> &&effects)
            : m_effects(std::move(effects))
        {
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const override;

        [[nodiscard]] const std::vector<
            std::unique_ptr<effects::IOneShotEffect>> &
        effects() const
        {
            return m_effects;
        }

    private:
        std::vector<std::unique_ptr<effects::IOneShotEffect>> m_effects;
    };
} // namespace dandan::abilities

#endif