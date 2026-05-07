#include "dandan/effects/one_shot/ETBEffect.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ETBEffect::apply(
        [[maybe_unused]] core::Game &game)
    {
        // This effect doesn't do anything by itself, it just serves as a marker
        // for replacement effects to modify it.
        return nullptr;
    }
} // namespace dandan::effects