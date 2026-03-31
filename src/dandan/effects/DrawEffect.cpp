#include "dandan/effects/DrawEffect.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace dandan::effects
{

    void DrawEffect::apply()
    {
        std::cout << "Applying draw effect\n";
    }

}