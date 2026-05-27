#ifndef DANDAN_SUMMONING_SICKNESS_CONDITION_H
#define DANDAN_SUMMONING_SICKNESS_CONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Card.h"

namespace dandan::conditions
{
    /**
     * A condition that checks whether a card has summoning sickness.
     * @class SummoningSicknessCondition
     *
     * @implements ICondition
     */
    class SummoningSicknessCondition : public ICondition
    {
    public:
        /** Constructor
         * @param card The card to check for summoning sickness
         */
        explicit SummoningSicknessCondition(core::Card &card) : m_card(card)
        {
        }
        [[nodiscard]] bool isSatisfied(const core::Game &game) const override;

    private:
        core::Card &m_card;
    };
} // namespace dandan::conditions

#endif