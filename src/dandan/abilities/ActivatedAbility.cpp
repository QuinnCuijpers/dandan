#include "dandan/abilities/ActivatedAbility.h"
#include <iostream>

namespace dandan::abilities
{
    void ActivatedAbility::resolve() const
    {
        std::cout << "Resolving Activated ability\n";
        m_cost->evaluate();
    }

} // namespace dandan::abilities