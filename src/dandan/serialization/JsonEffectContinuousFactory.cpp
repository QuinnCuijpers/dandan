#include "dandan/serialization/JsonEffectContinuousFactory.h"
#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
#include <string>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<effects::IContinuousEffect>::create_json(
        const effects::IContinuousEffect *effect)
    {
        auto json = nlohmann::json::object();
        const auto &registration{
            ContinuousEffectRegistry::instance().serializerFor(*effect)};

        auto data = registration.serializer(effect);

        if (registration.representation == JsonRepresentation::INLINE)
        {
            return data;
        }

        json["type"] = registration.name;
        json["data"] = data;

        return json;
    }

    std::unique_ptr<effects::IContinuousEffect> JsonFactory<
        effects::IContinuousEffect>::create_product(const nlohmann::json &json)
    {

        const auto &type = json.at("type").get<std::string>();
        return ContinuousEffectRegistry::instance().deserializerFor(type)(
            json.at("data"));
    }

} // namespace dandan::serialization
#endif // DANDAN_SERIALIZE
