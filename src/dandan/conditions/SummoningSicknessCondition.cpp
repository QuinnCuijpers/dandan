#include "dandan/conditions/SummoningSicknessCondition.h"
#include "dandan/core/Game.h"

namespace dandan::conditions
{

    bool SummoningSicknessCondition::isSatisfied(
        [[maybe_unused]] const core::Game &game) const
    {
        std::cout << "Checking summoning sickness condition for card "
                  << m_card.getData().getName()
                  << " (CardID: " << m_card.getID().getID() << ")\n";
        std::cout << "Card state: tapped=" << std::boolalpha
                  << m_card.getTapped()
                  << ", summoning_sick=" << m_card.getSummoningSickness()
                  << ", is_attacking=" << m_card.isAttacking() << "\n";
        // TODO: consider splitting this into two conditions, one for summoning
        // sickness and one for attacking status
        return m_card.getSummoningSickness() || m_card.isAttacking();
    }

} // namespace dandan::conditions