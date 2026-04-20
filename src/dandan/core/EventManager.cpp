#include "dandan/core/EventManager.h"
#include "dandan/abilities/TriggeredAbility.h"
#include <algorithm>

namespace dandan::core
{
    void EventManager::subscribe(const abilities::IAbility *ability)
    {
        if (const abilities::TriggeredAbility *triggered =
                dynamic_cast<const abilities::TriggeredAbility *>(ability))
        {
            m_subscribers.push_back(triggered);
        }
    }

    void EventManager::unsubscribe(const abilities::IAbility *ability)
    {
        auto it =
            std::remove(m_subscribers.begin(), m_subscribers.end(), ability);
        if (it != m_subscribers.end())
        {
            m_subscribers.erase(it, m_subscribers.end());
        }
    }

    void EventManager::notify(const events::IEvent &event) const
    {
        for (const auto *subscriber : m_subscribers)
        {
            if (subscriber->appliesToEvent(event))
            {
                subscriber->resolve();
            }
        }
    }
} // namespace dandan::core