#include "dandan/serialization/JsonConditionFactory.h"
#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/conditions/ControlsIslandCondition.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<conditions::ICondition>::create_json(
        [[maybe_unused]] const conditions::ICondition *condition)
    {
        if ([[maybe_unused]] const auto *controlsIslandCondition =
                dynamic_cast<const conditions::ControlsIslandCondition *>(
                    condition))
        {
            auto json = nlohmann::json{{"type", "ControlsIslandCondition"},
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

        if (type == "ControlsIslandCondition")
        {
            return std::make_unique<conditions::ControlsIslandCondition>();
        }

        throw std::runtime_error(
            "create_product for ICondition is not implemented yet.");
    }

} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE