#include "dandan/conditions/ControlsIslandCondition.h"
#include "dandan/core/Battlefield.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
#include "dandan/core/Player.h"
#include <algorithm>

namespace dandan::conditions
{
    bool ControlsIslandCondition::isSatisfied(const core::Game &game)
    {
        const core::Player &current_player = game.nonActivePlayer();
        const auto &battlefield{current_player.battlefield()};
        return std::any_of(battlefield.getPermanents().begin(),
                           battlefield.getPermanents().end(),
                           [](const core::Card &card)
                           {
                               return card.getData().getType() ==
                                          core::CardData::Type::Land &&
                                      card.getData().getSubType() ==
                                          core::CardData::SubType::Island;
                           });
    }
} // namespace dandan::conditions