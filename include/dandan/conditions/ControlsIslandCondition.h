#ifndef DANDAN_CONTROLSISLANDCONDITION_H
#define DANDAN_CONTROLSISLANDCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include <memory>

namespace dandan::conditions
{
    /**
     * @brief A condition that checks if the player controls the island.
     * @class ControlsIslandCondition
     *
     * @implements ICondition
     */
    class ControlsNoIslandCondition : public ICondition
    {
    public:
        [[nodiscard]] bool isSatisfied(const core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override
        {
            return std::make_unique<ControlsNoIslandCondition>();
        }
    };
} // namespace dandan::conditions

#endif
