#ifndef ENTERS_BATTLE_FIELD_EVENT_H
#define ENTERS_BATTLE_FIELD_EVENT_H

#include "IEvent.h"
#include "dandan/core/Card.h"
#include <memory>
#include <optional>

namespace dandan::events
{

    class ETBEvent : public IEvent
    {
    public:
        ETBEvent() = default;

        explicit ETBEvent(std::unique_ptr<core::Card> &&card)
            : m_source{std::move(card)}
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

        [[nodiscard]] bool equals(const IEvent &other) const override
        {
            const auto *otherETB = dynamic_cast<const ETBEvent *>(&other);
            if (otherETB == nullptr)
            {
                return false;
            }

            return m_tapped == otherETB->m_tapped;
        }

    private:
        // TODO: cant have this have a card as member
        // maybe take a pointer or reference to the card that triggered the
        // event instead of owning it?

        // but it needs to be default constructible for serialization, so maybe
        // an optional? but we also need to keep track of what triggered the
        // event
        std::optional<bool> m_tapped;
        // TODO: replace this with an actual source and not just cards
        std::optional<std::unique_ptr<core::Card>> m_source;
    };
} // namespace dandan::events

#endif