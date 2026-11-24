#ifndef DANDAN_ATTACKEFFECT_H
#define DANDAN_ATTACKEFFECT_H

#include <utility>

#include "dandan/core/Card.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"

namespace dandan::effects
{
    /** @brief A one-shot effect that changes a creature to be attacking
     * @class AttackEffect
     *
     * @implements IOneShotEffect
     */
    class AttackEffect : public IOneShotEffect
    {
    public:
        /** @brief Constructs an effect that marks a creature as attacking.
         * @param creature Creature to mark as attacking.
         * @param context Effect execution context.
         */
        explicit AttackEffect(core::Card &creature, EffectContext context);

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

    private:
        core::Card &m_creature;
    };
} // namespace dandan::effects

#endif
