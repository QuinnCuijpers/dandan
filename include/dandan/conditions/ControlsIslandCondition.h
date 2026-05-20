#ifndef DANDAN_CONTROLSISLANDCONDITION_H
#define DANDAN_CONTROLSISLANDCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"

namespace dandan::conditions
{
    /**
     * A condition that checks if the player controls the island.
     * @class ControlsIslandCondition
     *
     * @implements ICondition
     */
    class ControlsIslandCondition : public ICondition
    {
    public:
        bool isSatisfied(const core::Game &game) override;
    };
} // namespace dandan::conditions

#endif