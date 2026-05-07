#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/core/Game.h"
#include <iostream>

namespace dandan::abilities
{
    void ActivatedAbility::resolve([[maybe_unused]] core::Game &game) const
    {
        std::cout << "Resolving Activated ability\n";
        m_cost->evaluate();
    }

} // namespace dandan::abilities