#ifndef TRIGGERS_H
#define TRIGGERS_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/events/IEvent.h"

namespace dandan::triggers
{
    /** @brief An interface for defining triggers.
     * @class ITrigger
     */
    class ITrigger
    {
    public:
        ITrigger() = default;
        ITrigger(const ITrigger &) = delete;
        ITrigger(ITrigger &&) = delete;
        ITrigger &operator=(const ITrigger &) = delete;
        ITrigger &operator=(ITrigger &&) = delete;
        virtual ~ITrigger() = default;

        /** Determines if the trigger should trigger based on the given event
         * and context.
         * @param other The event to check against.
         * @param context The context in which the event occurred.
         * @return True if the trigger should activate, false otherwise.
         */
        [[nodiscard]] virtual bool triggersOn(
            const events::IEvent &other,
            abilities::AbilityContext context) const = 0;
    };

} // namespace dandan::triggers

#endif
