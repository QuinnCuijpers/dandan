#ifndef EVENTS_H
#define EVENTS_H

namespace dandan::events
{

    class IEvent
    {
    public:
        IEvent() = default;
        IEvent(const IEvent &) = delete;
        IEvent(IEvent &&) = delete;
        IEvent &operator=(const IEvent &) = delete;
        IEvent &operator=(IEvent &&) = delete;
        virtual ~IEvent() = default;
        [[nodiscard]] virtual bool equals(const IEvent &other) const = 0;
    };

} // namespace dandan::events

#endif