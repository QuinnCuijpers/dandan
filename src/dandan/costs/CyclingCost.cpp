#include "dandan/costs/CyclingCost.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace dandan::costs
{
    void CyclingCost::evaluate()
    {
        std::cout << "Evaluating CyclingCost\n";
        m_inner_cost->evaluate();
    }

}