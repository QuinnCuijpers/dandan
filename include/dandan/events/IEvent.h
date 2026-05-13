#ifndef EVENTS_H
#define EVENTS_H

#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"

namespace dandan::events
{

    class IEvent
    {
    public:
        explicit IEvent(core::CardID source, core::PlayerID controller)
            : m_source{source}, m_controller{controller}
        {
        }

        IEvent(const IEvent &) = delete;
        IEvent(IEvent &&) = delete;
        IEvent &operator=(const IEvent &) = delete;
        IEvent &operator=(IEvent &&) = delete;
        virtual ~IEvent() = default;

        [[nodiscard]] core::CardID source() const
        {
            return m_source;
        }

        [[nodiscard]] core::PlayerID controller() const
        {
            return m_controller;
        }

    private:
        [[maybe_unused]] core::CardID m_source;
        [[maybe_unused]] core::PlayerID m_controller;
    };

} // namespace dandan::events

#endif