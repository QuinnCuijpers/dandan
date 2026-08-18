#include "dandan/serialization/JsonAbilityFactory.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonTypeRegistry.h"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<abilities::IAbility>::create_json(
        const abilities::IAbility *ability)
    {
        auto json = nlohmann::json::object();
        const auto &registration{
            AbilityRegistry::instance().serializerFor(*ability)};

        auto data = registration.serializer(ability);

        if (registration.representation == JsonRepresentation::INLINE)
        {
            return data;
        }

        json["type"] = registration.name;
        json["data"] = data;

        return json;
    }

    std::unique_ptr<abilities::IAbility> JsonFactory<
        abilities::IAbility>::create_product(const nlohmann::json &json)
    {
        const auto &type = json.at("type").get<std::string>();
        return AbilityRegistry::instance().deserializerFor(type)(
            json.at("data"));
    }

} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE
