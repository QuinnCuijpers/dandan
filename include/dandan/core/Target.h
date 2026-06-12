#ifndef DANDAN_TARGET_H
#define DANDAN_TARGET_H

// 115.1. Some spells and abilities require their controller to choose one or
// more targets for them. The targets are object(s) and/or player(s) the spell
// or ability will affect. These targets are declared as part of the process of
// putting the spell or ability on the stack. The targets can’t be changed
// except by another spell or ability that explicitly says it can do so.

// 109.1. An object is an ability on the stack, a card, a copy of a card, a
// token, a spell, a permanent, or an emblem.

#include "dandan/abilities/BoundAbility.h"
#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include <iostream>
#include <variant>

namespace dandan::core
{
    using Target = std::variant<abilities::BoundAbility, PlayerID, CardID>;

    std::ostream &operator<<(std::ostream &ostream, const Target &target);

} // namespace dandan::core

#endif