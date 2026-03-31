#include "dandan/serialization/JsonReplaceFactory.h"
#include "dandan/effects/EntersTappedEffect.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<effects::IReplacementEffect>::create_json(const effects::IReplacementEffect *obj)
    {
        if (const auto *etb_tapped = dynamic_cast<const effects::EntersTappedEffect *>(obj))
        {
            return nlohmann::json{{"type", "EntersTappedEffect"}, {"data", nlohmann::json()}};
        }
        else
        {
            throw std::runtime_error("Unknown replacement effect type for JSON serialization");
        }
    }

    std::unique_ptr<effects::IReplacementEffect> JsonFactory<effects::IReplacementEffect>::create_product(const nlohmann::json &j)
    {
        const auto &type = j.at("type").get<std::string>();
        const auto &data = j.at("data");

        if (type == "EntersTappedEffect")
        {
            return std::make_unique<effects::EntersTappedEffect>();
        }
        else
        {
            throw std::runtime_error("Unknown replacement effect type: " + type);
        }
    }
}