#include "dandan/serialization/JsonEffectContinuousFactory.h"
#include "dandan/effects/continuous/prevention/BlockPreventionEffect.h"
#ifdef DANDAN_SERIALIZE
#include "dandan/conditions/ICondition.h"
#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/effects/continuous/replacement/EntersTappedEffect.h"
#include "dandan/serialization/JsonFactory.h"
#include <nlohmann/json.hpp>
#include <string>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<effects::IContinuousEffect>::create_json(
        [[maybe_unused]] const effects::IContinuousEffect *effect)
    {
        if ([[maybe_unused]] const auto *attackPreventionEffect =
                dynamic_cast<const effects::AttackPreventionEffect *>(effect))
        {
            auto json = nlohmann::json{{"type", "AttackPreventionEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["condition"] =
                JsonFactory<conditions::ICondition>::create_json(
                    attackPreventionEffect->getCondition());
            return json;
        }
        if (const auto *blockPreventionEffect =
                dynamic_cast<const effects::BlockPreventionEffect *>(effect))
        {
            auto json = nlohmann::json{{"type", "BlockPreventionEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["condition"] =
                JsonFactory<conditions::ICondition>::create_json(
                    blockPreventionEffect->getCondition());
            return json;
        }
        if ([[maybe_unused]] const auto *entersTappedEffect =
                dynamic_cast<const effects::EntersTappedEffect *>(effect))
        {
            auto json = nlohmann::json{{"type", "EntersTappedEffect"},
                                       {"data", nlohmann::json::object()}};
            return json;
        }
        throw std::runtime_error("create_json for this type of "
                                 "IContinuousEffect is not implemented yet.");
    }

    std::unique_ptr<effects::IContinuousEffect> JsonFactory<
        effects::IContinuousEffect>::
        create_product([[maybe_unused]] const nlohmann::json &json)
    {
        const std::string type{json.at("type").get<std::string>()};
        const nlohmann::json &data{json.at("data")};

        if (type == "AttackPreventionEffect")
        {
            auto condition =
                JsonFactory<conditions::ICondition>::create_product(
                    data.at("condition"));
            return std::make_unique<effects::AttackPreventionEffect>(
                std::move(condition));
        }
        if (type == "EntersTappedEffect")
        {
            return std::make_unique<effects::EntersTappedEffect>();
        }

        throw std::runtime_error(
            "create_product for IContinuousEffect is not implemented yet.");
    }
} // namespace dandan::serialization
#endif // DANDAN_SERIALIZE