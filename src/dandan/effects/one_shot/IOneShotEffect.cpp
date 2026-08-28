#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/Game.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> IOneShotEffect::apply(
        core::ExecutionContext exec_ctx) const
    {
        auto event = apply_impl(exec_ctx);
        exec_ctx.state.get().conditionManager().checkConditions(exec_ctx);
        return event;
    }
} // namespace dandan::effects
