#include "dandan/serialization/JsonConditionFactory.h"
#ifdef DANDAN_SERIALIZE
#include "dandan/conditions/ICondition.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{

    nlohmann::json JsonFactory<conditions::ICondition>::create_json(
        const conditions::ICondition *condition)
    {
        auto json = nlohmann::json::object();
        const auto &registration{
            ConditionRegistry::instance().serializerFor(*condition)};

        auto data = registration.serializer(condition);

        if (registration.representation == JsonRepresentation::INLINE)
        {
            return data;
        }

        json["type"] = registration.name;
        json["data"] = data;

        return json;
    }

    std::unique_ptr<conditions::ICondition> JsonFactory<
        conditions::ICondition>::create_product(const nlohmann::json &json)
    {

        const auto &type = json.at("type").get<std::string>();
        return ConditionRegistry::instance().deserializerFor(type)(
            json.at("data"));
    }

} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE
