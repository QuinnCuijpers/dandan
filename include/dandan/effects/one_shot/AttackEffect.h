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
        /** Constructor
         * @param creature The creature to apply the effect to.
         */
        explicit AttackEffect(core::Card &creature, EffectContext context)
            : IOneShotEffect(std::move(context)), m_creature{creature}
        {
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<AttackEffect>(m_creature,
                                                  getEffectContext());
        }

    private:
        core::Card &m_creature;
    };
} // namespace dandan::effects

#endif