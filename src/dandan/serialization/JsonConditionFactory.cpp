#include "dandan/serialization/JsonConditionFactory.h"
#ifdef DANDAN_SERIALIZE
#include "dandan/conditions/ControlsNoIslandCondition.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<conditions::ICondition>::create_json(
        [[maybe_unused]] const conditions::ICondition *condition)
    {
        if ([[maybe_unused]] const auto *controlsNoIslandCondition =
                dynamic_cast<const conditions::ControlsNoIslandCondition *>(
                    condition))
        {
            auto json = nlohmann::json{{"type", "ControlsNoIslandCondition"},
                                       {"data", nlohmann::json::object()}};
            return json;
        }
        throw std::runtime_error(
            "create_json for this type of ICondition is not "
            "implemented yet.");
    }

    std::unique_ptr<conditions::ICondition> JsonFactory<
        conditions::ICondition>::
        create_product([[maybe_unused]] const nlohmann::json &json)
    {
        const std::string type{json.at("type").get<std::string>()};
        // const nlohmann::json &data{json.at("data")};

        if (type == "ControlsNoIslandCondition")
        {
            return std::make_unique<conditions::ControlsNoIslandCondition>();
        }

        throw std::runtime_error(
            "create_product for ICondition is not implemented yet.");
    }

} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE