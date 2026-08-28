#include "dandan/conditions/StartingPlayerCondition.h"

namespace dandan::conditions
{
    [[nodiscard]] bool StartingPlayerCondition::isSatisfied(
        const core::ExecutionContext exec_ctx,
        [[maybe_unused]] std::optional<effects::EffectContext> context) const
    {
        auto &game{exec_ctx.state.get()};

        return game.isFirstTurn();
    }

    [[nodiscard]] std::unique_ptr<ICondition> StartingPlayerCondition::clone()
        const
    {
        return std::make_unique<StartingPlayerCondition>();
    }
} // namespace dandan::conditions
