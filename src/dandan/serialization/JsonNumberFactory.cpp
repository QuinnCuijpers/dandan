#include "dandan/serialization/JsonNumberFactory.h"
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/GraveyardCount.h"

namespace dandan::serialization
{
    nlohmann::json JsonFactory<numbers::INumber>::create_json(
        const numbers::INumber *number)
    {
        auto json = nlohmann::json{{"type", "ExactNumber"},
                                   {"data", nlohmann::json::object()}};
        if (const auto *graveyard_count =
                dynamic_cast<const numbers::GraveyardCount *>(number))
        {
            json["type"] = "GraveyardCount";
            json["data"]["card_name"] = graveyard_count->getName();
            return json;
        }
        // Handle other INumber types here
        throw std::runtime_error("Unknown INumber type");
    }

    std::unique_ptr<numbers::INumber> JsonFactory<
        numbers::INumber>::create_product(const nlohmann::json &json)
    {
        const auto &type = json.at("type").get<std::string>();
        const auto &data = json.at("data");

        if (type == "ExactNumber")
        {
            int value = data.at("value").get<int>();
            return std::make_unique<numbers::ExactNumber>(value);
        }
        if (type == "GraveyardCount")
        {
            std::string name = data.at("card_name").get<std::string>();
            return std::make_unique<numbers::GraveyardCount>(name);
        }
        // Handle other INumber types here
        throw std::runtime_error("Unknown INumber type in JSON");
    }
} // namespace dandan::serialization