#include "dandan/abilities/ActivatedAbility.h"
#include <iostream>
#include <nlohmann/json.hpp>

namespace dandan::abilities
{
    void ActivatedAbility::resolve() const
    {
        std::cout << "Resolving Activated ability\n";
        m_cost->evaluate();
        m_effect->apply();
    }

} // namespace dandan::abilities