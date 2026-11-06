#include "dandan/events/IEvent.h"

namespace dandan::events
{
    IEvent::IEvent(core::CardID source, core::PlayerID controller)
        : m_source{source}, m_controller{controller}
    {
    }

    core::CardID IEvent::source() const
    {
        return m_source;
    }
} // namespace dandan::events
