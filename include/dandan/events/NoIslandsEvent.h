#ifndef DANDAN_NOISLANDSEVENT_H
#define DANDAN_NOISLANDSEVENT_H

#include "dandan/events/IEvent.h"

namespace dandan::events
{
    class NoIslandsEvent : public IEvent
    {
    public:
        explicit NoIslandsEvent(core::CardID card_id, core::PlayerID controller)
            : IEvent(card_id, controller)
        {
        }
    };
} // namespace dandan::events

#endif // DANDAN_NOISLANDSEVENT_H