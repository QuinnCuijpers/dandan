#include "dandan/triggers/SelfETBtrigger.h"
#include "dandan/events/ETBEvent.h"
#include "dandan/log.h"

namespace dandan::triggers
{
    bool SelfETBTrigger::triggersOn(const events::IEvent &other,
                                    abilities::AbilityContext context) const
    {
        DLOGI << "Checking SelfETBTrigger against event\n";
        const auto *otherETB = dynamic_cast<const events::ETBEvent *>(&other);
        if (otherETB == nullptr)
        {
            return false;
        }

        if (m_tapped.has_value() && otherETB->isTapped() != m_tapped.value())
        {
            DLOGI << "Tapped state does not match\n";
            return false;
        }
        if (context.source_card_id.getID() != otherETB->source().getID())
        {
            DLOGI << "Card ID: " << context.source_card_id.getID()
                  << " does not match event source ID: "
                  << otherETB->source().getID() << "\n";
            return false;
        }
        DLOGI << "SelfETBTrigger matches event\n";
        return true;
    }
} // namespace dandan::triggers