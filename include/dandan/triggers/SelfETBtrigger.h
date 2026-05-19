

#ifndef DANDAN_SELFETBTRIGGER_H
#define DANDAN_SELFETBTRIGGER_H

#include "ITrigger.h"
#include "dandan/events/ETBEvent.h"
#include <optional>

namespace dandan::triggers
{

    class SelfETBTrigger : public ITrigger
    {
    public:
        SelfETBTrigger() = default;

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

        [[nodiscard]] bool isTapped() const
        {
            return m_tapped.value_or(false);
        }

        [[nodiscard]] bool triggersOn(
            const events::IEvent &other,
            abilities::AbilityContext context) const override;

    private:
        std::optional<bool> m_tapped;
    };
} // namespace dandan::triggers

#endif