#ifndef DANDAN_NOISLANDSEVENT_H
#define DANDAN_NOISLANDSEVENT_H

#include "dandan/events/IEvent.h"

namespace dandan::events
{
    /** @brief Event generated when a cplayer controls no islands
     * @class NoIslandsEvent
     *
     * @implements IEvent
     */
    class NoIslandsEvent : public IEvent
    {
    public:
        /** Constructor
         * @param card_id The CardID of the source card that generated the
         * event
         * @param controller The Controller of the source card
         */
        explicit NoIslandsEvent(core::CardID card_id, core::PlayerID controller)
            : IEvent(card_id, controller)
        {
        }
    };
} // namespace dandan::events

#endif // DANDAN_NOISLANDSEVENT_H
