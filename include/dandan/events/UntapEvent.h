#ifndef DANDAN_UNTAPEVENT_H
#define DANDAN_UNTAPEVENT_H

#include "dandan/core/Card.h"
#include "dandan/events/IEvent.h"

namespace dandan::events
{
    class UntapEvent : public IEvent
    {
    public:
        explicit UntapEvent(core::Card &card)
            : IEvent(card.getID(), card.getControllerID())
        {
        }
    };
} // namespace dandan::events

#endif // DANDAN_UNTAPEVENT_H