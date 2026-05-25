#include "dandan/conditions/PlayedLandCondition.h"
#include "dandan/core/Game.h"

namespace dandan::conditions
{
    bool PlayedLandCondition::isSatisfied(const core::Game &game) const
    {
        return game.activePlayer().playedLandThisTurn();
    }
} // namespace dandan::conditions