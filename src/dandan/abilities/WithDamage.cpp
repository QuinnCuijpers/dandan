#include "dandan/abilities/WithDamage.h"
#include "dandan/abilities/AbilityContext.h"
#include <iostream>

namespace dandan::abilities
{

    void WithDamage::resolve(core::Game &game, AbilityContext context) const
    {
        m_ability->resolve(game, context);
        std::cout << "Resolving WithDamage decorator\n";
        std::cout << "Dealing " << m_damage << " damage\n";
    }
} // namespace dandan::abilities