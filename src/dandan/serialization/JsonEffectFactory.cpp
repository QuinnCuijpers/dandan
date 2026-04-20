#include "dandan/serialization/JsonEffectFactory.h"
#include "dandan/effects/BounceLandEffect.h"
#include "dandan/effects/DrawEffect.h"
#include "dandan/effects/ETBEffect.h"
#include "dandan/effects/PeekEffect.h"
#include "dandan/effects/ScryEffect.h"
#include "nlohmann/json_fwd.hpp"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<effects::IEffect>::create_json(
        const effects::IEffect *effect)
    {

        if (const auto *scryEffect =
                dynamic_cast<const effects::ScryEffect *>(effect))
        {
            auto j = nlohmann::json{{"type", "ScryEffect"},
                                    {"data", nlohmann::json::object()}};
            j["data"]["scry_amount"] = scryEffect->m_scry_amount;
            return j;
        }
        else if (const auto *peekEffect =
                     dynamic_cast<const effects::PeekEffect *>(effect))
        {
            auto j = nlohmann::json{{"type", "PeekEffect"},
                                    {"data", nlohmann::json::object()}};
            j["data"]["peek_amount"] = peekEffect->m_peek_amount;
            return j;
        }
        else if (const auto *drawEffect =
                     dynamic_cast<const effects::DrawEffect *>(effect))
        {
            auto j = nlohmann::json{{"type", "DrawEffect"},
                                    {"data", nlohmann::json::object()}};
            j["data"]["amount"] = drawEffect->m_amount;
            return j;
        }
        else if (const auto *etbEffect =
                     dynamic_cast<const effects::ETBEffect *>(effect))
        {
            auto j = nlohmann::json{{"type", "ETBEffect"},
                                    {"data", nlohmann::json::object()}};
            j["data"]["tapped"] = etbEffect->m_tapped;
            return j;
        }
        else if ([[maybe_unused]] const auto *bounceLandEffect =
                     dynamic_cast<const effects::BounceLandEffect *>(effect))
        {
            auto j = nlohmann::json{{"type", "BounceLandEffect"},
                                    {"data", nlohmann::json::object()}};
            return j;
        }
        else
        {
            throw std::runtime_error(
                "Unknown effect type for JSON serialization: " +
                std::string(typeid(*effect).name()));
        }
    }

    std::unique_ptr<effects::IEffect> JsonFactory<
        effects::IEffect>::create_product(const nlohmann::json &j)
    {
        const auto &type = j.at("type").get<std::string>();
        const auto &data = j.at("data");

        if (type == "ScryEffect")
        {
            return std::make_unique<effects::ScryEffect>(
                data.at("scry_amount").get<int>());
        }
        else if (type == "PeekEffect")
        {
            return std::make_unique<effects::PeekEffect>(
                data.at("peek_amount").get<int>());
        }
        else if (type == "DrawEffect")
        {
            return std::make_unique<effects::DrawEffect>(
                data.at("amount").get<int>());
        }
        else if (type == "ETBEffect")
        {
            auto etbEffect = std::make_unique<effects::ETBEffect>();
            if (data.contains("tapped"))
            {
                etbEffect->setTapped(data.at("tapped").get<bool>());
            }
            return etbEffect;
        }
        else if (type == "BounceLandEffect")
        {
            return std::make_unique<effects::BounceLandEffect>();
        }
        else
        {
            throw std::runtime_error("Unknown effect type: " + type);
        }
    }
} // namespace dandan::serialization