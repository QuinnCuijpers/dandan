#include "dandan/serialization/JsonFactory.h"
#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
#include <string>

namespace dandan::serialization
{
    template <typename T>
    std::unique_ptr<T> create_product(const nlohmann::json &json)
    {
        const auto &type = json.at("type").get<std::string>();
        return JsonTypeRegistry<T>::instance().deserializerFor(type)(
            json["data"]);
    }

    template <typename T> nlohmann::json create_json(const T *obj)
    {
        auto json = nlohmann::json::object();
        const auto &registration{
            JsonTypeRegistry<T>::instance().serializerFor(*obj)};

        auto data = registration.serializer(obj);

        if (registration.representation == JsonRepresentation::INLINE)
        {
            return data;
        }

        json["type"] = registration.name;
        json["data"] = data;

        return json;
    }

} // namespace dandan::serialization
#endif // DANDAN_SERIALIZE
