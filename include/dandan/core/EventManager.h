#ifndef DANDAN_CORE_EVENTMANAGER_H
#define DANDAN_CORE_EVENTMANAGER_H

#include "dandan/abilities/EventTriggeredAbility.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/events/IEvent.h"
#include <unordered_map>
#include <vector>

namespace dandan::core
{
    /** @brief Manages triggered abilities and event notifications.
     * @class EventManager
     */
    class EventManager
    {
    public:
        /** Subscribes a card to the event manager.
         * @param card The card to subscribe.
         */
        void subscribe(const Card &card);

        void subscribe(abilities::EventTriggeredAbility &ability);

        /** Unsubscribes a card from the event manager.
         * @param card The card to unsubscribe.
         */
        void unsubscribe(const Card &card);

        /** Notifies all subscribers of an event.
         * @param event The event to notify subscribers of.
         * @param game The game instance.
         */
        void notify(const events::IEvent &event, core::Game &game) const;

        /** Gets the number of subscribers.
         * @return The number of subscribers.
         */
        [[nodiscard]] size_t size() const
        {
            return m_subscribers.size();
        }

    private:
        std::unordered_map<
            CardID, std::vector<const abilities::EventTriggeredAbility *>>
            m_subscribers;
    };
} // namespace dandan::core

#endif // DANDAN_CORE_EVENTMANAGER_H
