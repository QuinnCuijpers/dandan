#ifndef ENTERS_BATTLE_FIELD_EVENT_H
#define ENTERS_BATTLE_FIELD_EVENT_H

#include "IEvent.h"
#include <optional>

namespace dandan::events
{

    class ETBEvent : public IEvent
    {
    public:
        explicit ETBEvent(core::CardID card_id) : IEvent{card_id}
        {
        }

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

        [[nodiscard]] bool isTapped() const
        {
            return m_tapped.value_or(false);
        }

    private:
        std::optional<bool> m_tapped;
    };
} // namespace dandan::events

#endif