#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/engine/ConditionManager.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> IOneShotEffect::apply(
        core::ExecutionContext exec_ctx) const
    {
        auto &condition_manager{exec_ctx.condition_manager.get()};
        auto event = apply_impl(exec_ctx);
        condition_manager.checkConditions(exec_ctx);
        return event;
    }
} // namespace dandan::effects
