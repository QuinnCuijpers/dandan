#include "dandan/abilities/WithDamage.h"
#include <iostream>

namespace dandan::abilities
{

    void WithDamage::resolve(core::Game &game) const
    {
        m_ability->resolve(game);
        std::cout << "Resolving WithDamage decorator\n";
        std::cout << "Dealing " << m_damage << " damage\n";
    }
} // namespace dandan::abilities