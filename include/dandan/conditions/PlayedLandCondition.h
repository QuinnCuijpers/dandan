#ifndef DANDAN_PLAYEDLANDCONDITION_H
#define DANDAN_PLAYEDLANDCONDITION_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/core/TextReplacement.h"
#include <memory>
#include <optional>
#include <vector>

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
            const core::Game &game,
            std::optional<abilities::AbilityContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override
        {
            return std::make_unique<PlayedLandCondition>();
        }
    };
} // namespace dandan::conditions

#endif
