#include "dandan/abilities/StaticAbility.h"
#include <iostream>
#include <nlohmann/json.hpp>

namespace dandan::abilities
{

    void StaticAbility::resolve() const
    {
        std::cout << "Resolving StaticAbility\n";
    }
} // namespace dandan::abilities