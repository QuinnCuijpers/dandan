#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/engine/ConditionManager.h"
#include <stdexcept>
#include <utility>

namespace dandan::effects
{
    IOneShotEffect::IOneShotEffect(EffectContext effect_context)
        : m_effect_context(std::move(effect_context))
    {
    }

    std::string IOneShotEffect::display() const
    {
        throw std::runtime_error("Unimplemented display");
    }

    std::unique_ptr<events::IEvent> IOneShotEffect::apply(
        core::ExecutionContext exec_ctx) const
    {
        auto &condition_manager{exec_ctx.condition_manager.get()};
        auto event = apply_impl(exec_ctx);
        condition_manager.checkConditions(exec_ctx);
        return event;
    }

    EffectContext IOneShotEffect::getEffectContext() const
    {
        return m_effect_context;
    }
} // namespace dandan::effects
