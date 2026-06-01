#include "dandan/costs/SelfSacrificeCost.h"

namespace dandan::costs
{
    std::string SelfSacrificeCost::display(bool isFinal) const
    {
        if (isFinal)
        {
            return "Sacrifice this Card: ";
        }
        return "Sacrifice this Card";
    }

} // namespace dandan::costs