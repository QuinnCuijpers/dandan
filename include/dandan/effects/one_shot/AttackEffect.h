#ifndef DANDAN_ATTACKEFFECT_H
#define DANDAN_ATTACKEFFECT_H

#include "dandan/core/Card.h"

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
        explicit AttackEffect(core::Card &creature) : m_creature{creature}
        {
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<AttackEffect>(m_creature);
        }

    private:
        core::Card &m_creature;
    };
} // namespace dandan::effects

#endif