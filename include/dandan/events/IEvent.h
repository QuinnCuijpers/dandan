#ifndef EVENTS_H
#define EVENTS_H

#include <nlohmann/json_fwd.hpp>

namespace dandan::events
{

    class IEvent
    {
    public:
        virtual ~IEvent() = default;
        virtual void to_json(nlohmann::json &j, const IEvent &event) const = 0;
    };

} // namespace dandan::events

#endif