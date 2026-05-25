#ifndef ENTERS_BATTLE_FIELD_EVENT_H
#define ENTERS_BATTLE_FIELD_EVENT_H

#include "IEvent.h"
#include <optional>

namespace dandan::events
{
    /** Event generated when a card enters the battlefield
     * @class ETBEvent
     *
     * @implements IEvent
     */
    class ETBEvent : public IEvent
    {
    public:
        /** Constructor
         * @param card_id The CardID of the source card that generated the event
         * @param controller The Controller of the source card
         */
        explicit ETBEvent(core::CardID card_id, core::PlayerID controller)
            : IEvent{card_id, controller}
        {
        }

        // void setTapped(bool tapped)
        // {
        //     m_tapped = tapped;
        // }

        /** query whether the card entered tapped
         * @returns a boolean representing whether the card entered tapped
         */
        [[nodiscard]] bool isTapped() const
        {
            return m_tapped.value_or(false);
        }

    private:
        std::optional<bool> m_tapped;
    };
} // namespace dandan::events

#endif