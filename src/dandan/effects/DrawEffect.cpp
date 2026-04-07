#include "dandan/effects/DrawEffect.h"
#include <iostream>
#include <nlohmann/json.hpp>

namespace dandan::effects
{

    void DrawEffect::apply()
    {
        std::cout << "Applying draw effect\n";
    }

} // namespace dandan::effects