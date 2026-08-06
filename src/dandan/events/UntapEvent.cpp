#include "dandan/events/UntapEvent.h"

namespace dandan::events
{
    UntapEvent::UntapEvent(core::Card &card)
        : IEvent(card.getID(), card.getControllerID())
    {
    }
} // namespace dandan::events
