#include "dandan/events/ETBEvent.h"

namespace dandan::events
{
    ETBEvent::ETBEvent(core::CardID card_id, core::PlayerID controller)
        : IEvent{card_id, controller}
    {
    }

    [[nodiscard]] bool ETBEvent::isTapped() const
    {
        return m_tapped.value_or(false);
    }

} // namespace dandan::events
