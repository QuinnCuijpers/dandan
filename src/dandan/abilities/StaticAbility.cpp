#include "dandan/abilities/StaticAbility.h"
#include <iostream>

namespace dandan::abilities
{

    void StaticAbility::resolve([[maybe_unused]] core::Game &game) const
    {
        std::cout << "Resolving StaticAbility\n";
    }
} // namespace dandan::abilities