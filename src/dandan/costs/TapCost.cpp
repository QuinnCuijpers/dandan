#include "dandan/costs/TapCost.h"

namespace dandan::costs
{
    std::string TapCost::display([[maybe_unused]] bool isFinal) const
    {
        if (isFinal)
        {
            return "[T]: ";
        }
        return "[T]";
    }

} // namespace dandan::costs