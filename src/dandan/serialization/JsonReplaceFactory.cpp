#include "dandan/serialization/JsonReplaceFactory.h"
#include "dandan/replacement_effects/EntersTappedEffect.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<replacement_effects::IReplacementEffect>::
        create_json(const replacement_effects::IReplacementEffect *obj)
    {

        if ([[maybe_unused]]
            const auto *etb_tapped =
                dynamic_cast<const replacement_effects::EntersTappedEffect *>(
                    obj))
        {
            return nlohmann::json{{"type", "EntersTappedEffect"},
                                  {"data", nlohmann::json::object()}};
        }
        else
        {
            throw std::runtime_error(
                "Unknown replacement effect type for JSON serialization");
        }
    }

    std::unique_ptr<replacement_effects::IReplacementEffect> JsonFactory<
        replacement_effects::IReplacementEffect>::
        create_product(const nlohmann::json &j)
    {
        [[maybe_unused]]
        const auto &data = j.at("data");

        const auto &type = j.at("type").get<std::string>();

        if (type == "EntersTappedEffect")
        {
            return std::make_unique<replacement_effects::EntersTappedEffect>();
        }
        else
        {
            throw std::runtime_error("Unknown replacement effect type: " +
                                     type);
        }
    }
} // namespace dandan::serialization