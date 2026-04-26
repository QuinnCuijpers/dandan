#include "dandan/effects/one_shot/DrawEffect.h"

#include <iostream>

namespace dandan::effects
{

    void DrawEffect::apply()
    {
        std::cout << "Applying draw effect\n";
    }

} // namespace dandan::effects