#ifndef DANDAN_CONTROLSISLANDCONDITION_H
#define DANDAN_CONTROLSISLANDCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"

namespace dandan::conditions
{
    class ControlsIslandCondition : public ICondition
    {
    public:
        /// Checks if the player controls the island.
        bool isSatisfied(const core::Game &game) override;
    };
} // namespace dandan::conditions

#endif