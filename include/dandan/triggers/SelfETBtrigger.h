

#ifndef DANDAN_SELFETBTRIGGER_H
#define DANDAN_SELFETBTRIGGER_H

#include "ITrigger.h"
#include "dandan/events/ETBEvent.h"
#include <iostream>
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
            abilities::AbilityContext context) const override
        {
            std::cout << "Checking SelfETBTrigger against event\n";
            const auto *otherETB =
                dynamic_cast<const events::ETBEvent *>(&other);
            if (otherETB == nullptr)
            {
                return false;
            }

            if (m_tapped.has_value() &&
                otherETB->isTapped() != m_tapped.value())
            {
                std::cout << "Tapped state does not match\n";
                return false;
            }
            if (context.source_card_id.getID() != otherETB->source().getID())
            {
                std::cout << "Card ID: " << context.source_card_id.getID()
                          << " does not match event source ID: "
                          << otherETB->source().getID() << "\n";
                return false;
            }
            std::cout << "SelfETBTrigger matches event\n";
            return true;
        }

    private:
        std::optional<bool> m_tapped;
    };
} // namespace dandan::triggers

#endif