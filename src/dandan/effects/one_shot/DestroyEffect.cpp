#include "dandan/effects/one_shot/DestroyEffect.h"
#include "dandan/core/ExecutionContext.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    DestroyEffect::DestroyEffect(core::Card &card, EffectContext context)
        : IOneShotEffect(std::move(context)), m_card{card}
    {
    }

    std::unique_ptr<IOneShotEffect> DestroyEffect::copy() const
    {
        return std::make_unique<DestroyEffect>(m_card, getEffectContext());
    }

    std::unique_ptr<events::IEvent> DestroyEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        m_card.destroy(exec_ctx);
        return nullptr;
    }
} // namespace dandan::effects
