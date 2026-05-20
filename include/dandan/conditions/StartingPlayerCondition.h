#ifndef DANDAN_STARTINGPLAYERCONDITION_H
#define DANDAN_STARTINGPLAYERCONDITION_H

#include "dandan/conditions/ICondition.h"

namespace dandan::conditions
{
    /**
     * A condition that checks if the player is the starting player and it is
     * the first turn. This is used to determine whether the player should draw
     * a card at the beginning of their turn.
     * @class StartingPlayerCondition
     *
     * @implements ICondition
     */
    class StartingPlayerCondition : public ICondition
    {
    public:
        bool isSatisfied(const core::Game &game) override
        {
            return game.isFirstTurn();
        }
    };
} // namespace dandan::conditions

#endif