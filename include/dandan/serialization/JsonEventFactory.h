#ifndef DANDAN_JSONEVENTFACTORY_H
#define DANDAN_JSONEVENTFACTORY_H

#ifdef DANDAN_BUILD_SERIALIZE

#include "JsonFactory.h"
#include "dandan/events/IEvent.h"

namespace dandan::serialization
{
    template <> class JsonFactory<events::IEvent>
    {
    public:
        static std::unique_ptr<dandan::events::IEvent> create_product(
            const nlohmann::json &json);

        static nlohmann::json create_json(const dandan::events::IEvent *event);
    };
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE

#endif // DANDAN_JSONEVENTFACTORY_H