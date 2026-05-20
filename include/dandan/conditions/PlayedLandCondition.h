#ifndef DANDAN_PLAYEDLANDCONDITION_H
#define DANDAN_PLAYEDLANDCONDITION_H

#include "dandan/conditions/ICondition.h"

namespace dandan::conditions
{
    /**
     * A condition that checks if the player has played a land this turn.
     * @class PlayedLandCondition
     *
     * @implements ICondition
     */
    class PlayedLandCondition : public ICondition
    {
    public:
        bool isSatisfied(const core::Game &game) override;
    };
} // namespace dandan::conditions

#endif