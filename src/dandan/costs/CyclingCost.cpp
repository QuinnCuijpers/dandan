#include "dandan/costs/CyclingCost.h"
#include <iostream>
#include <nlohmann/json.hpp>

namespace dandan::costs
{

    void CyclingCost::evaluate()
    {
        std::cout << "Evaluating CyclingCost\n";
        m_inner_cost->evaluate();
    }

} // namespace dandan::costs