#include "dandan/serialization/JsonEffectOneShotFactory.h"
#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/effects/one_shot/BounceLandEffect.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/effects/one_shot/ETBEffect.h"
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
            json["data"]["amount"] = drawEffect->m_amount;
            return json;
        }
        if (const auto *etbEffect =
                dynamic_cast<const effects::ETBEffect *>(effect))
        {
            auto json = nlohmann::json{{"type", "ETBEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["tapped"] = etbEffect->m_tapped;
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
            return std::make_unique<effects::DrawEffect>(
                data.at("amount").get<int>());
        }
        if (type == "ETBEffect")
        {
            auto etbEffect = std::make_unique<effects::ETBEffect>();
            if (data.contains("tapped"))
            {
                etbEffect->setTapped(data.at("tapped").get<bool>());
            }
            return etbEffect;
        }
        if (type == "BounceLandEffect")
        {
            return std::make_unique<effects::BounceLandEffect>();
        }
        if (type == "SelfSacrificeEffect")
        {
            return std::make_unique<effects::SelfSacrificeEffect>();
        }
        throw std::runtime_error("Unknown effect type: " + type);
    }
} // namespace dandan::serialization
#endif // DANDAN_BUILD_SERIALIZE