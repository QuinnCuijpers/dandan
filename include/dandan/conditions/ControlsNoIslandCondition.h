#ifndef DANDAN_CONTROLSNOISLANDCONDITION_H
#define DANDAN_CONTROLSNOISLANDCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include <memory>

namespace dandan::conditions
{
    /**
     * @brief A condition that checks if the player controls no island.
     * @class ControlsNoIslandCondition
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
