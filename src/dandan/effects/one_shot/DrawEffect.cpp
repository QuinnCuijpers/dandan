#include "dandan/effects/one_shot/DrawEffect.h"

#include <iostream>

namespace dandan::effects
{

    void DrawEffect::apply([[maybe_unused]] core::Game &game)
    {
        std::cout << "Applying draw effect\n";
    }

} // namespace dandan::effects