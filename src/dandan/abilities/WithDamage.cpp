#include "dandan/abilities/WithDamage.h"
#include "dandan/abilities/ManaAbility.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace dandan::abilities
{

    void WithDamage::resolve()
    {
        m_ability->resolve();
        std::cout << "Resolving WithDamage decorator\n";
        std::cout << "Dealing " << m_damage << " damage\n";
    }
} // namespace dandan::abilities