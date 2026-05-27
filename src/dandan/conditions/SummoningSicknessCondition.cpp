#include "dandan/conditions/SummoningSicknessCondition.h"
#include "dandan/core/Game.h"

namespace dandan::conditions
{

    bool SummoningSicknessCondition::isSatisfied(
        [[maybe_unused]] const core::Game &game) const
    {
        return m_card.getSummoningSickness();
    }

} // namespace dandan::conditions