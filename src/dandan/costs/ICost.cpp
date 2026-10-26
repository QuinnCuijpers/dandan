#include "dandan/costs/ICost.h"
#include <stdexcept>

namespace dandan::costs
{
    std::string ICost::display([[maybe_unused]] bool isFinal) const
    {
        throw std::runtime_error("Unimplemented display");
    }
} // namespace dandan::costs
