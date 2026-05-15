#include "dandan/conditions/PlayedLandCondition.h"

namespace dandan::conditions
{
    bool PlayedLandCondition::isSatisfied(const core::Game &game)
    {
        return game.activePlayer().playedLandThisTurn();
    }
} // namespace dandan::conditions