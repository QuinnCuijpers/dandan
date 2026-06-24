#include "dandan/serialization/JsonNumberFactory.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/numbers/ConditionalNumber.h"
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/GraveyardCount.h"
#include "dandan/numbers/INumber.h"
#include "dandan/serialization/JsonFactory.h"
#include <memory>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<numbers::INumber>::create_json(
        const numbers::INumber *number)
    {
        auto json = nlohmann::json::object();
        if (const auto *exact =
                dynamic_cast<const numbers::ExactNumber *>(number))
        {
            return exact->getValue();
        }
        if (const auto *graveyard_count =
                dynamic_cast<const numbers::GraveyardCount *>(number))
        {
            json["type"] = "GraveyardCount";
            json["data"]["card_name"] = graveyard_count->getName();
            return json;
        }
        if (const auto *condition_number =
                dynamic_cast<const numbers::ConditionalNumber *>(number))
        {
            json["type"] = "conditionalNumber";
            json["data"]["ifNumber"] =
                create_json(condition_number->getIfNumber());
            json["data"]["elseNumber"] =
                create_json(condition_number->getElseNumber());
            json["data"]["condition"] =
                JsonFactory<conditions::ICondition>::create_json(
                    condition_number->getCondition());
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
        if (type == "conditionalNumber")
        {
            auto condition{JsonFactory<conditions::ICondition>::create_product(
                data.at("condition"))};

            try
            {
                int if_{data.at("ifNumber")};
                int else_{data.at("elseNumber")};
                return std::make_unique<numbers::ConditionalNumber>(
                    if_, else_, std::move(condition));
            }
            catch (...)
            {
                auto if_{create_product(data.at("ifNumber"))};
                auto else_{create_product(data.at("elseNumber"))};
                return std::make_unique<numbers::ConditionalNumber>(
                    std::move(if_), std::move(else_), std::move(condition));
            }
        }
        // Handle other INumber types here
        throw std::runtime_error("Unknown INumber type in JSON");
    }
} // namespace dandan::serialization