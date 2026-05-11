#ifndef DANDAN_NOISLANDSEVENT_H
#define DANDAN_NOISLANDSEVENT_H

#include "dandan/core/Card.h"
#include "dandan/events/IEvent.h"
namespace dandan::events
{
    class NoIslandsEvent : public IEvent
    {
    public:
        explicit NoIslandsEvent(core::CardID card_id) : IEvent(card_id)
        {
        }
    };
} // namespace dandan::events

#endif // DANDAN_NOISLANDSEVENT_H