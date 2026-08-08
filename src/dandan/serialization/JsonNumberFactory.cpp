#include "dandan/serialization/JsonNumberFactory.h"
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/INumber.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{

    nlohmann::json JsonFactory<numbers::INumber>::create_json(
        const numbers::INumber *number)
    {
        auto json = nlohmann::json::object();
        const auto &registration{
            NumberRegistry::instance().serializerFor(*number)};

        auto data = registration.serializer(number);

        if (registration.representation == JsonRepresentation::INLINE)
        {
            return data;
        }

        json["type"] = registration.name;
        json["data"] = data;

        return json;
    }

    std::unique_ptr<numbers::INumber> JsonFactory<
        numbers::INumber>::create_product(const nlohmann::json &json)
    {
        if (json.is_number_integer())
        {
            return std::make_unique<numbers::ExactNumber>(json.get<int>());
        }
        const auto &type = json.at("type").get<std::string>();
        return NumberRegistry::instance().deserializerFor(type)(
            json.at("data"));
    }

} // namespace dandan::serialization
