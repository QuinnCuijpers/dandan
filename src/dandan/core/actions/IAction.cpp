#include "dandan/core/actions/IAction.h"

namespace dandan::core
{
    ActionActor IAction::getActor() const
    {
        return std::monostate{};
    }
} // namespace dandan::core
