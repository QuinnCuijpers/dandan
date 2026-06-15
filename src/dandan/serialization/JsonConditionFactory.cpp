#include "dandan/serialization/JsonConditionFactory.h"
#include "dandan/core/CardData.h"
#include "dandan/core/SubType.h"
#ifdef DANDAN_SERIALIZE
#include "dandan/conditions/DefenderControlsNoBasicCondition.h"
#include "dandan/conditions/SelfControlsNoBasicCondition.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<conditions::ICondition>::create_json(
        [[maybe_unused]] const conditions::ICondition *condition)
    {
        if (const auto *selfControlsNoIslandCondition =
                dynamic_cast<const conditions::SelfControlsNoBasicCondition *>(
                    condition))
        {
            auto json = nlohmann::json{{"type", "SelfControlsNoBasicCondition"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["type"] = selfControlsNoIslandCondition->type();
            return json;
        }
        if (const auto *defenderControlsNoBasicCondition = dynamic_cast<
                const conditions::DefenderControlsNoBasicCondition *>(
                condition))
        {
            auto json =
                nlohmann::json{{"type", "DefenderControlsNoBasicCondition"},
                               {"data", nlohmann::json::object()}};
            json["data"]["type"] = defenderControlsNoBasicCondition->type();
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
        const nlohmann::json &data{json.at("data")};

        if (type == "SelfControlsNoBasicCondition")
        {
            return std::make_unique<conditions::SelfControlsNoBasicCondition>(
                data.at("type").get<core::SubType>());
        }
        if (type == "DefenderControlsNoBasicCondition")
        {

            return std::make_unique<
                conditions::DefenderControlsNoBasicCondition>(
                data.at("type").get<core::SubType>());
        }

        throw std::runtime_error(
            "create_product for ICondition is not implemented yet.");
    }

} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE