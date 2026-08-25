#include "dandan/effects/one_shot/DestroyEffect.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> DestroyEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        m_card.destroy(exec_ctx);
        return nullptr;
    }
} // namespace dandan::effects
