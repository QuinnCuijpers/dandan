#ifndef DANDAN_ABILITYEXECUTIONCONTEXT_H
#define DANDAN_ABILITYEXECUTIONCONTEXT_H

#include "dandan/core/CardRegistry.h"
#include "dandan/core/engine/InputManager.h"
#include <functional>

namespace dandan::core
{
    class GameState;
    class EventManager;
    class ConditionManager;
    class PreventionManager;
    class PriorityManager;
    class ReplacementManager;
    class SBAManager;

    struct ExecutionContext
    {
        std::reference_wrapper<core::GameState> state;
        std::reference_wrapper<core::CardRegistry> cards;
        std::reference_wrapper<InputManager> input_manager;
        std::reference_wrapper<EventManager> event_manager;
        std::reference_wrapper<PreventionManager> prevention_manager;
        std::reference_wrapper<ReplacementManager> replacement_manager;
        std::reference_wrapper<PriorityManager> priority_manager;
        std::reference_wrapper<ConditionManager> condition_manager;
        std::reference_wrapper<SBAManager> sba_manager;
    };
} // namespace dandan::core
#endif
