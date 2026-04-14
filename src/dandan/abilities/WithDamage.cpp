#include "dandan/abilities/WithDamage.h"
#include <iostream>

namespace dandan::abilities
{

    void WithDamage::resolve() const
    {
        m_ability->resolve();
        std::cout << "Resolving WithDamage decorator\n";
        std::cout << "Dealing " << m_damage << " damage\n";
    }
} // namespace dandan::abilities