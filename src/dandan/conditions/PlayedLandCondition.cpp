#include "dandan/conditions/PlayedLandCondition.h"
#include "dandan/core/Game.h"
#include <optional>

namespace dandan::conditions
{
    bool PlayedLandCondition::isSatisfied(
        const core::ExecutionContext exec_ctx,
        [[maybe_unused]] std::optional<effects::EffectContext> context) const
    {
        auto &game{exec_ctx.state.get()};

        return game.activePlayer().playedLandThisTurn();
    }

    [[nodiscard]] std::unique_ptr<ICondition> PlayedLandCondition::clone() const
    {
        return std::make_unique<PlayedLandCondition>();
    }
} // namespace dandan::conditions
