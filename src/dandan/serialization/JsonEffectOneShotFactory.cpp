#include "dandan/serialization/JsonEffectOneShotFactory.h"
#include "dandan/effects/one_shot/PutCardOnTopEffect.h"
#ifdef DANDAN_SERIALIZE
#include "dandan/effects/one_shot/BounceLandEffect.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/effects/one_shot/PeekEffect.h"
#include "dandan/effects/one_shot/ScryEffect.h"
#include "dandan/effects/one_shot/SelfSacrificeEffect.h"
#include "nlohmann/json_fwd.hpp"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<effects::IOneShotEffect>::create_json(
        const effects::IOneShotEffect *effect)
    {

        if (const auto *scryEffect =
                dynamic_cast<const effects::ScryEffect *>(effect))
        {
            auto json = nlohmann::json{{"type", "ScryEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["scry_amount"] = scryEffect->m_scry_amount;
            return json;
        }
        if (const auto *peekEffect =
                dynamic_cast<const effects::PeekEffect *>(effect))
        {
            auto json = nlohmann::json{{"type", "PeekEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["peek_amount"] = peekEffect->m_peek_amount;
            return json;
        }
        if (const auto *drawEffect =
                dynamic_cast<const effects::DrawEffect *>(effect))
        {
            auto json = nlohmann::json{{"type", "DrawEffect"},
                                       {"data", nlohmann::json::object()}};
            auto *number{drawEffect->getNumber().get()};
            if (const auto *exactNumber =
                    dynamic_cast<const numbers::ExactNumber *>(number))
            {
                json["data"]["amount"] = exactNumber->getValue();
            }
            else
            {
                json["data"]["amount"] =
                    JsonFactory<numbers::INumber>::create_json(number);
            }
            return json;
        }
        if ([[maybe_unused]] const auto *bounceLandEffect =
                dynamic_cast<const effects::BounceLandEffect *>(effect))
        {
            auto json = nlohmann::json{{"type", "BounceLandEffect"},
                                       {"data", nlohmann::json::object()}};
            return json;
        }
        if (dynamic_cast<const effects::SelfSacrificeEffect *>(effect) !=
            nullptr)
        {
            auto json = nlohmann::json{{"type", "SelfSacrificeEffect"},
                                       {"data", nlohmann::json::object()}};
            return json;
        }
        if (const auto *putCardOnTopEffect =
                dynamic_cast<const effects::PutCardOnTopEffect *>(effect))
        {
            auto json = nlohmann::json{{"type", "PutCardOnTopEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["amount"] = putCardOnTopEffect->getAmount();
            return json;
        }

        throw std::runtime_error(
            "Unknown effect type for JSON serialization: " +
            std::string(typeid(*effect).name()));
    }

    std::unique_ptr<effects::IOneShotEffect> JsonFactory<
        effects::IOneShotEffect>::create_product(const nlohmann::json &json)
    {
        const auto &type = json.at("type").get<std::string>();
        const auto &data = json.at("data");

        if (type == "ScryEffect")
        {
            return std::make_unique<effects::ScryEffect>(
                data.at("scry_amount").get<int>());
        }
        if (type == "PeekEffect")
        {
            return std::make_unique<effects::PeekEffect>(
                data.at("peek_amount").get<int>());
        }
        if (type == "DrawEffect")
        {
            try
            {
                auto number{data.at("amount").get<int>()};
                return std::make_unique<effects::DrawEffect>(number);
            }
            catch (const nlohmann::json::exception &e)
            {
                const auto &amount_json = data.at("amount");
                auto amount =
                    JsonFactory<numbers::INumber>::create_product(amount_json);
                return std::make_unique<effects::DrawEffect>(std::move(amount));
            }
        }
        if (type == "BounceLandEffect")
        {
            return std::make_unique<effects::BounceLandEffect>();
        }
        if (type == "SelfSacrificeEffect")
        {
            return std::make_unique<effects::SelfSacrificeEffect>();
        }
        if (type == "PutCardOnTopEffect")
        {
            return std::make_unique<effects::PutCardOnTopEffect>(
                data.at("amount").get<int>());
        }
        throw std::runtime_error("Unknown effect type: " + type);
    }
} // namespace dandan::serialization
#endif // DANDAN_SERIALIZE