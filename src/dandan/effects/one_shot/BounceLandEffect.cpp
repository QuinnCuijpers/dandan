#include "dandan/effects/one_shot/BounceLandEffect.h"
#include <iostream>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> BounceLandEffect::apply(
        [[maybe_unused]] core::Game &game)
    {
        std::cout << "Applying BounceLandEffect\n";
        return nullptr;
    }
} // namespace dandan::effects