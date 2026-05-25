

#ifndef DANDAN_SELFETBTRIGGER_H
#define DANDAN_SELFETBTRIGGER_H

#include "ITrigger.h"
#include <optional>

namespace dandan::triggers
{
    /** A trigger that activates when the card it's attached to in the
     * `EventManager` enters the battlefield.
     * @class SelfETBTrigger
     *
     * @implements ITrigger
     */
    class SelfETBTrigger : public ITrigger
    {
    public:
        SelfETBTrigger() = default;

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
            abilities::AbilityContext context) const override;

    private:
        std::optional<bool> m_tapped;
    };
} // namespace dandan::triggers

#endif