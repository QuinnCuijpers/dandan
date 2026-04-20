#ifndef ENTERS_BATTLE_FIELD_EVENT_H
#define ENTERS_BATTLE_FIELD_EVENT_H

#include "IEvent.h"
#include <optional>

namespace dandan::events
{

    struct ETBEvent final : public IEvent
    {
        std::optional<bool> m_tapped;

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }
        [[nodiscard]] bool isTapped() const
        {
            return m_tapped.value_or(false);
        }

        [[nodiscard]] bool equals(const IEvent &other) const override
        {
            const auto *otherETB = dynamic_cast<const ETBEvent *>(&other);
            if (otherETB == nullptr)
            {
                return false;
            }

            return m_tapped == otherETB->m_tapped;
        }
    };
} // namespace dandan::events

#endif