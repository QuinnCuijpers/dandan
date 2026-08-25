#ifndef DANDAN_ABILITYEXECUTIONCONTEXT_H
#define DANDAN_ABILITYEXECUTIONCONTEXT_H

#include "dandan/core/CardRegistry.h"
#include <functional>

namespace dandan::core
{
    class Game;
}

namespace dandan::core
{
    struct ExecutionContext
    {
        std::reference_wrapper<core::Game> state;
        std::reference_wrapper<core::CardRegistry> cards;
    };
} // namespace dandan::core
#endif
