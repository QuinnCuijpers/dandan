
#ifndef DANDAN_ETBTRIGGER_H
#define DANDAN_ETBTRIGGER_H

#include "ITrigger.h"
#include "dandan/events/ETBEvent.h"
#include "dandan/events/IEvent.h"
#include <optional>

namespace dandan::triggers
{
    /** @brief A trigger that activates when a card enters the battlefield.
     * @class ETBTrigger
     *
     * @implements ITrigger
     */
    class ETBTrigger : public ITrigger
    {
    public:
        ETBTrigger() = default;

        /** Sets whether to only trigger on tapped ETB events or not.
         * @param tapped The tapped status to set.
         */
        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

        /** Returns whether the trigger is set to only trigger on tapped ETB
         * events.
         * @return True if the trigger is set to only trigger on tapped ETB
         * events, false otherwise.
         */
        [[nodiscard]] bool isTapped() const
        {
            return m_tapped.value_or(false);
        }

        [[nodiscard]] bool triggersOn(
            const events::IEvent &other,
            [[maybe_unused]] abilities::AbilityContext context) const override
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
