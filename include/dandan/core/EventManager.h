#ifndef DANDAN_CORE_EVENTMANAGER_H
#define DANDAN_CORE_EVENTMANAGER_H

#include "dandan/abilities/IAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/events/IEvent.h"
#include <unordered_map>
#include <vector>

namespace dandan::core
{
    class EventManager
    {
    public:
        void subscribe(const Card &card);
        void unsubscribe(const Card &card);
        void notify(const events::IEvent &event, core::Game &game) const;

        [[nodiscard]] size_t size() const
        {
            return m_subscribers.size();
        }

    private:
        std::unordered_map<CardID, std::vector<const abilities::IAbility *>>
            m_subscribers;
    };
} // namespace dandan::core

#endif // DANDAN_CORE_EVENTMANAGER_H