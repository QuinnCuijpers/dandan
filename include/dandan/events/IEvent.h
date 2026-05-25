#ifndef EVENTS_H
#define EVENTS_H

#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"

namespace dandan::events
{
    /** @brief Abstract class represeting the base for all events
     *@class IEvent
     */
    class IEvent
    {
    public:
        /** Constructor
         * @param source The CardID of the source card that generated the event
         * @param controller The Controller of the source card
         */
        explicit IEvent(core::CardID source, core::PlayerID controller)
            : m_source{source}, m_controller{controller}
        {
        }

        IEvent(const IEvent &) = delete;
        IEvent(IEvent &&) = delete;
        IEvent &operator=(const IEvent &) = delete;
        IEvent &operator=(IEvent &&) = delete;
        virtual ~IEvent() = default;

        /** returns the source of the event.
         * @returns the CardID of the card that generated this event
         *
         */
        [[nodiscard]] core::CardID source() const
        {
            return m_source;
        }

        /**
         * get the controller of the card that generated the event
         * @returns The PlayerID of the player that controls the card that
         * generated the event
         */
        [[nodiscard]] core::PlayerID controller() const
        {
            return m_controller;
        }

    private:
        // TODO: consider having this be a std::variant between card and player
        // id
        [[maybe_unused]] core::CardID m_source;
        [[maybe_unused]] core::PlayerID m_controller;
    };

} // namespace dandan::events

#endif
