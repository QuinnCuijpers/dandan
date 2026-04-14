#ifndef ENTERS_BATTLE_FIELD_EVENT_H
#define ENTERS_BATTLE_FIELD_EVENT_H

#include "IEvent.h"
#include <optional>

namespace dandan::events
{

    struct ETBEvent final : public IEvent
    {
        std::optional<bool> m_tapped{};

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }
        bool isTapped() const
        {
            return m_tapped.value_or(false);
        }

        bool equals(const IEvent &other) const override
        {
            const ETBEvent *otherETB = dynamic_cast<const ETBEvent *>(&other);
            if (!otherETB)
                return false;

            return m_tapped == otherETB->m_tapped;
        }
    };
} // namespace dandan::events

#endif