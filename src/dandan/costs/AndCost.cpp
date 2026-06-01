#include "dandan/costs/AndCost.h"

namespace dandan::costs
{

    std::string AndCost::display(bool isFinal) const
    {
        std::string res{};
        res += m_first->display(false);
        res += ", ";
        res += m_second->display(isFinal);
        return res;
    }

} // namespace dandan::costs