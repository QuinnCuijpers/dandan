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
        /// The current game state.
        std::reference_wrapper<core::GameState> state;
        /// The registry used to look up card instances.
        std::reference_wrapper<core::CardRegistry> cards;
        /// The manager used to request player input.
        std::reference_wrapper<InputManager> input_manager;
        /// The manager that dispatches game events.
        std::reference_wrapper<EventManager> event_manager;
        /// The manager that tracks prevention effects.
        std::reference_wrapper<PreventionManager> prevention_manager;
        /// The manager that tracks replacement effects.
        std::reference_wrapper<ReplacementManager> replacement_manager;
        /// The manager that controls priority and timing.
        std::reference_wrapper<PriorityManager> priority_manager;
        /// The manager that tracks state-triggered conditions.
        std::reference_wrapper<ConditionManager> condition_manager;
        /// The manager that checks and applies state-based actions.
        std::reference_wrapper<SBAManager> sba_manager;
    };
} // namespace dandan::core
#endif
