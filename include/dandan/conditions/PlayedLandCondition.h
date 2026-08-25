#ifndef DANDAN_PLAYEDLANDCONDITION_H
#define DANDAN_PLAYEDLANDCONDITION_H

#include "dandan/conditions/ICondition.h"
#include <memory>
#include <optional>

namespace dandan::conditions
{
    /**
     * @brief A condition that checks if the player has played a land this turn.
     * @class PlayedLandCondition
     *
     * @implements ICondition
     */
    class PlayedLandCondition : public ICondition
    {
    public:
        [[nodiscard]] bool isSatisfied(
            core::ExecutionContext exec_ctx,
            std::optional<effects::EffectContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override;
    };
} // namespace dandan::conditions

#endif
