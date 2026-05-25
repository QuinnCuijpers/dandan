#ifndef DANDAN_UNTAPEVENT_H
#define DANDAN_UNTAPEVENT_H

#include "dandan/core/Card.h"
#include "dandan/events/IEvent.h"

namespace dandan::events
{
    /** @brief Event generated when a card becomes untapped
     * @class UntapEvent
     *
     * @implements IEvent
     */

    class UntapEvent : public IEvent
    {
    public:
        /** Constructor
         * @param card The card that was untapped
         */
        explicit UntapEvent(core::Card &card)
            : IEvent(card.getID(), card.getControllerID())
        {
        }
    };
} // namespace dandan::events

#endif // DANDAN_UNTAPEVENT_H
