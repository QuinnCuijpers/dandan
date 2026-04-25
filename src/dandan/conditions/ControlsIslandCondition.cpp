#include "dandan/conditions/ControlsIslandCondition.h"
#include "dandan/core/Battlefield.h"
#include "dandan/core/Card.h"
#include <algorithm>

namespace dandan::conditions
{
    bool ControlsIslandCondition::isSatisfied()
    {
        const auto &battlefield{m_player.getBattlefield()};
        return std::any_of(battlefield.getPermanents().begin(),
                           battlefield.getPermanents().end(),
                           [](const std::unique_ptr<core::Card> &card)
                           {
                               return card->getType() == core::Card::Land &&
                                      card->getSubType() ==
                                          core::Card::SubType::Island;
                           });
    }
} // namespace dandan::conditions