#ifndef EVENTS_H
#define EVENTS_H

namespace dandan::events
{

    class IEvent
    {
    public:
        virtual ~IEvent() = default;
        virtual bool equals(const IEvent &other) const = 0;
    };

} // namespace dandan::events

#endif