#ifndef DANDAN_NOISLANDSEVENT_H
#define DANDAN_NOISLANDSEVENT_H

#include "dandan/events/IEvent.h"
namespace dandan::events
{
    class NoIslandsEvent : public IEvent
    {
    public:
        [[nodiscard]] bool equals(const IEvent &other) const override
        {
            return dynamic_cast<const NoIslandsEvent *>(&other) != nullptr;
        }
    };
} // namespace dandan::events

#endif // DANDAN_NOISLANDSEVENT_H