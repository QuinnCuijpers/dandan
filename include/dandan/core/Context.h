#ifndef DANDAN_CONTEXT_H
#define DANDAN_CONTEXT_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/effects/EffectContext.h"
#include <variant>
namespace dandan::core
{
    using Context =
        std::variant<effects::EffectContext, abilities::AbilityContext>;
}

#endif