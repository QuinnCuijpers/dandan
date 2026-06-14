#include "dandan/triggers/SelfETBtrigger.h"
#include "dandan/events/ETBEvent.h"
#include "dandan/log.h"
#include <iostream>

namespace dandan::triggers
{
    bool SelfETBTrigger::triggersOn(const events::IEvent &other,
                                    abilities::AbilityContext context) const
    {
        std::cout << "Checking SelfETBTrigger against event\n";
        const auto *otherETB = dynamic_cast<const events::ETBEvent *>(&other);
        if (otherETB == nullptr)
        {
            return false;
        }

        if (m_tapped.has_value() && otherETB->isTapped() != m_tapped.value())
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
} // namespace dandan::triggers