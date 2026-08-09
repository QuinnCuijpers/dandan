#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonCostFactory.h"
#include "dandan/costs/ICost.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<costs::ICost>::create_json(
        const costs::ICost *cost)
    {
        auto json = nlohmann::json::object();
        const auto &registration{
            CostsRegistry::instance().serializerFor(*cost)};

        auto data = registration.serializer(cost);

        if (registration.representation == JsonRepresentation::INLINE)
        {
            return data;
        }

        json["type"] = registration.name;
        json["data"] = data;

        return json;
    }

    std::unique_ptr<costs::ICost> JsonFactory<costs::ICost>::create_product(
        const nlohmann::json &json)
    {

        const auto &type = json.at("type").get<std::string>();
        return CostsRegistry::instance().deserializerFor(type)(json.at("data"));
    }

} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE
