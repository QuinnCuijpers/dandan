#ifndef DANDAN_CORE_EVENTMANAGER_H
#define DANDAN_CORE_EVENTMANAGER_H

#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/events/IEvent.h"
#include <unordered_map>

namespace dandan::core
{
    /** @brief Manages triggered abilities and event notifications.
     * @class EventManager
     */
    class EventManager
    {
    public:
        void subscribe(abilities::BoundAbility &ability);

        /** Unsubscribes a card from the event manager.
         * @param card The card to unsubscribe.
         */
        void unsubscribe(const Card &card);

        void unsubscribe(const abilities::BoundAbility &ability);

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
        std::unordered_map<CardID, std::vector<abilities::BoundAbility *>>
            m_subscribers;
    };
} // namespace dandan::core

#endif // DANDAN_CORE_EVENTMANAGER_H
