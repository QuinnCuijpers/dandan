#include "dandan/effects/one_shot/DestroyEffect.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> DestroyEffect::apply_impl(
        core::Game &game) const
    {
        m_card.destroy(game);
        return nullptr;
    }
} // namespace dandan::effects