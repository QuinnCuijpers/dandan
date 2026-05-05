#ifndef DANDAN_STARTINGPLAYERCONDITION_H
#define DANDAN_STARTINGPLAYERCONDITION_H

#include "dandan/conditions/ICondition.h"

namespace dandan::conditions
{
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