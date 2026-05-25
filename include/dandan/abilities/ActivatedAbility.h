#ifndef DANDAN_ACTIVATED_ABILITY_H
#define DANDAN_ACTIVATED_ABILITY_H

#include "IAbility.h"
#include "dandan/core/Game.h"
#include "dandan/costs/ICost.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>

namespace dandan::abilities
{
    /** @brief An activated ability is any ability that can be activated by a player at
     * instant speed. It consists of a cost that must be paid to activate the
     * ability and an effect that is applied when the ability resolves.
     * @class ActivatedAbility
     *
     * @implements IAbility
     */
    class ActivatedAbility final : public IAbility
    {
    public:
        /** Constructor
         * @param cost The cost to activate the ability
         * @param effect The effect of the ability
         */
        ActivatedAbility(std::unique_ptr<costs::ICost> cost,
                         std::unique_ptr<effects::IOneShotEffect> effect)
            : m_cost(std::move(cost)), m_effect(std::move(effect))
        {
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const override;

        /** Get the cost of the ability
         * @return The cost of the ability
         */
        [[nodiscard]] const costs::ICost *getCost() const
        {
            return m_cost.get();
        }

        /** Get the effect of the ability
         * @return The effect of the ability
         */
        [[nodiscard]] const effects::IOneShotEffect *getEffect() const
        {
            return m_effect.get();
        }

        [[nodiscard]] bool canActivate(core::Game &game,
                                       AbilityContext context) const override;

    private:
        std::unique_ptr<costs::ICost> m_cost;
        std::unique_ptr<effects::IOneShotEffect> m_effect;
    };
} // namespace dandan::abilities

#endif
