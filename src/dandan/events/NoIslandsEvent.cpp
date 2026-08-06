#include "dandan/events/NoIslandsEvent.h"

namespace dandan::events
{
    NoIslandsEvent::NoIslandsEvent(core::CardID card_id,
                                   core::PlayerID controller)
        : IEvent(card_id, controller)
    {
    }
} // namespace dandan::events
