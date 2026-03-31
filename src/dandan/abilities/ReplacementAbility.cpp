#include "dandan/abilities/ReplacementAbility.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace dandan::abilities
{

    void ReplacementAbility::resolve()
    {
        std::cout << "Resolving ReplacementAbility\n";
    }
}