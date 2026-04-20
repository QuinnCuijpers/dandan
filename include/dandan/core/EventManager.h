#ifndef DANDAN_CORE_EVENTMANAGER_H
#define DANDAN_CORE_EVENTMANAGER_H

#include "dandan/abilities/IAbility.h"
#include "dandan/events/IEvent.h"
#include <vector>

namespace dandan::core
{
    class EventManager
    {
    public:
        EventManager() = default;

        void subscribe(const abilities::IAbility *ability);
        void unsubscribe(const abilities::IAbility *ability);
        void notify(const events::IEvent &event) const;

    private:
        std::vector<const abilities::IAbility *> m_subscribers{};
    };
} // namespace dandan::core

#endif