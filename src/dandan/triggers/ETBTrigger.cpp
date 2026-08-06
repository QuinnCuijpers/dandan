#include "dandan/triggers/ETBtrigger.h"
#include "dandan/events/ETBEvent.h"

namespace dandan::triggers
{
    template <bool self_trigger>
    [[nodiscard]] bool ETBTrigger<self_trigger>::triggersOn(
        const events::IEvent &other,
        [[maybe_unused]] abilities::AbilityContext context) const
    {

        const auto *otherETB = dynamic_cast<const events::ETBEvent *>(&other);

        if (otherETB == nullptr)
        {
            return false;
        }

        if constexpr (self_trigger)
        {

            if (context.source_card_id.getID() != otherETB->source().getID())
            {
                return false;
            }
        }

        if (m_tapped.has_value() && otherETB->isTapped() != m_tapped.value())
        {
            return false;
        }

        return true;
    }

    template class ETBTrigger<false>;
    template class ETBTrigger<true>;

} // namespace dandan::triggers
