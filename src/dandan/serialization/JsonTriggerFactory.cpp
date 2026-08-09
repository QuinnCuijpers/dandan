#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonTriggerFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include "dandan/triggers/ITrigger.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<triggers::ITrigger>::create_json(
        const triggers::ITrigger *trigger)
    {
        auto json = nlohmann::json::object();
        const auto &registration{
            TriggerRegistry::instance().serializerFor(*trigger)};

        auto data = registration.serializer(trigger);

        if (registration.representation == JsonRepresentation::INLINE)
        {
            return data;
        }

        json["type"] = registration.name;
        json["data"] = data;

        return json;
    }

    std::unique_ptr<triggers::ITrigger> JsonFactory<
        triggers::ITrigger>::create_product(const nlohmann::json &json)
    {
        const auto &type = json.at("type").get<std::string>();
        return TriggerRegistry::instance().deserializerFor(type)(
            json.at("data"));
    }

} // namespace dandan::serialization
#endif // DANDAN_SERIALIZE
