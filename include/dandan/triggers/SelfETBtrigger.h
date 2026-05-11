

#ifndef DANDAN_SELFETBTRIGGER_H
#define DANDAN_SELFETBTRIGGER_H

#include "ITrigger.h"
#include "dandan/core/CardID.h"
#include "dandan/events/ETBEvent.h"
#include <optional>

namespace dandan::triggers
{

    class SelfETBTrigger : public ITrigger
    {
    public:
        explicit SelfETBTrigger(core::CardID card_id) : m_card_id(card_id)
        {
        }

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

        void setSourceCardID(core::CardID card_id)
        {
            m_card_id = card_id;
        }

        [[nodiscard]] bool isTapped() const
        {
            return m_tapped.value_or(false);
        }

        [[nodiscard]] bool triggersOn(
            const events::IEvent &other) const override
        {
            const auto *otherETB =
                dynamic_cast<const events::ETBEvent *>(&other);
            if (otherETB == nullptr)
            {
                return false;
            }

            if (m_tapped.has_value() &&
                otherETB->isTapped() != m_tapped.value())
            {
                return false;
            }

            return m_card_id == otherETB->source();
        }

    private:
        std::optional<bool> m_tapped;
        core::CardID m_card_id;
    };
} // namespace dandan::triggers

#endif