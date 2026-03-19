#include "dandan/IManaDecorator.h"

void WithDamage::resolve()
{
    std::cout << "Resolving WithDamage decorator\n";
    std::cout << "Dealing " << m_damage << " damage\n";
    m_ability->resolve();
}