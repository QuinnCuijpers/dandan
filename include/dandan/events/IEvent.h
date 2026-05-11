#ifndef EVENTS_H
#define EVENTS_H

#include "dandan/core/CardID.h"

namespace dandan::events
{

    class IEvent
    {
    public:
        explicit IEvent(core::CardID source) : m_source{source}
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

    private:
        [[maybe_unused]] core::CardID m_source;
    };

} // namespace dandan::events

#endif