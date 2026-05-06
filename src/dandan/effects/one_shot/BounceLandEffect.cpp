#include "dandan/effects/one_shot/BounceLandEffect.h"
#include <iostream>

namespace dandan::effects
{
    void BounceLandEffect::apply([[maybe_unused]] core::Game &game)
    {
        std::cout << "Applying BounceLandEffect\n";
    }
} // namespace dandan::effects