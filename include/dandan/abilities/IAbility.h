#ifndef IABILITY_H
#define IABILITY_H

#include "dandan/abilities/AbilityContext.h"

namespace dandan::core
{
    class Game;
}

namespace dandan::events
{
    class IEvent;
}

namespace dandan::abilities
{
    /** The interface for all abilities
     * @class IAbility
     */
    class IAbility
    {
    public:
        IAbility() = default;
        IAbility(const IAbility &) = delete;
        IAbility(IAbility &&) = delete;
        IAbility &operator=(const IAbility &) = delete;
        IAbility &operator=(IAbility &&) = delete;
        virtual ~IAbility() = default;

        /** Resolve the ability
         * @param game The game object to mutate when the ability is resolving
         * @param context The context for the ability's execution
         */
        virtual void resolve(core::Game &game,
                             AbilityContext context) const = 0;

        /** Determine if the ability applies to a given event
         * @param event The event to check
         * @param context The context for the ability's execution
         * @return True if the ability applies to the event, false otherwise.
         * The default implementation returns false.
         */
        [[nodiscard]] virtual bool appliesTo(
            [[maybe_unused]] const events::IEvent &event,
            [[maybe_unused]] abilities::AbilityContext context) const
        {
            return false;
        }
    };
}; // namespace dandan::abilities

#endif