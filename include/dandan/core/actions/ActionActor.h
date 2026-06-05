#ifndef DANDAN_ACTIONACTOR_H
#define DANDAN_ACTIONACTOR_H

#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include <variant>

namespace dandan::core
{
    using ActionActor = std::variant<std::monostate, PlayerID, CardID>;

} // namespace dandan::core

#endif