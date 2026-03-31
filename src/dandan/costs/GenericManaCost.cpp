#include "dandan/costs/GenericManaCost.h"
#include "dandan/abilities/IAbility.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace dandan::costs
{
    void GenericManaCost::evaluate()
    {
        std::cout << "Evaluating GenericManaCost with " << m_amount << " mana\n";
    }

}