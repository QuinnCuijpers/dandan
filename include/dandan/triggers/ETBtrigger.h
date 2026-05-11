
#ifndef DANDAN_ETBTRIGGER_H
#define DANDAN_ETBTRIGGER_H

#include "ITrigger.h"
#include "dandan/events/ETBEvent.h"
#include "dandan/events/IEvent.h"
#include <optional>

namespace dandan::triggers
{

    class ETBTrigger : public ITrigger
    {
    public:
        ETBTrigger() = default;

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
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
            return true;
        }

    private:
        std::optional<bool> m_tapped;
    };
} // namespace dandan::triggers

#endif