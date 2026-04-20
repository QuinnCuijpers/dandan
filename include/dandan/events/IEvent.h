#ifndef EVENTS_H
#define EVENTS_H

namespace dandan::events
{

    class IEvent
    {
    public:
        IEvent() = default;
        IEvent(const IEvent &) = default;
        IEvent(IEvent &&) = delete;
        IEvent &operator=(const IEvent &) = default;
        IEvent &operator=(IEvent &&) = delete;
        virtual ~IEvent() = default;
        [[nodiscard]] virtual bool equals(const IEvent &other) const = 0;
    };

} // namespace dandan::events

#endif