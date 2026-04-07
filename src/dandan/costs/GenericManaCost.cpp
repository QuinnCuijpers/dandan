#include "dandan/costs/GenericManaCost.h"
#include <iostream>
#include <nlohmann/json.hpp>

namespace dandan::costs
{
    void GenericManaCost::evaluate()
    {
        std::cout << "Evaluating GenericManaCost with " << m_amount << " mana\n";
    }

} // namespace dandan::costs