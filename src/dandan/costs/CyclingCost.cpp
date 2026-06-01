#include "dandan/costs/CyclingCost.h"

namespace dandan::costs
{
    std::string CyclingCost::display(bool isFinal) const
    {
        std::string res{};
        res += m_inner_cost->display(isFinal);
        res += ", Discard this card: ";
        return res;
    }
} // namespace dandan::costs