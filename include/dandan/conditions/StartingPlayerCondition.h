#ifndef DANDAN_STARTINGPLAYERCONDITION_H
#define DANDAN_STARTINGPLAYERCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include <memory>
#include <optional>

namespace dandan::conditions
{
    /**
     * @brief A condition that checks if the player is the starting player and
     * it is the first turn. This is used to determine whether the player should
     * draw a card at the beginning of their turn.
     * @class StartingPlayerCondition
     *
     * @implements ICondition
     */
    class StartingPlayerCondition : public ICondition
    {
    public:
        [[nodiscard]] bool isSatisfied(
            const core::Game &game,
            [[maybe_unused]] std::optional<effects::EffectContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override;
    };
} // namespace dandan::conditions

#endif
