#include "dandan/serialization/JsonCostFactory.h"
#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/costs/CyclingCost.h"
#include "dandan/costs/ICost.h"
#include "dandan/costs/ManaCost.h"
#include "dandan/costs/SelfSacrificeCost.h"
#include "dandan/mana/Mana.h"
#include "dandan/serialization/JsonManaFactory.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<costs::ICost>::create_json(
        const costs::ICost *cost)
    {
        if (const auto *cycle_cost =
                dynamic_cast<const costs::CyclingCost *>(cost))
        {
            auto json = nlohmann::json{{"type", "CyclingCost"},
                                       {"data", nlohmann::json::object()}};

            const auto *const inner_cost = cycle_cost->getInnerCost();
            json["data"]["inner_cost"] = create_json(inner_cost);
            return json;
        }
        if (const auto *mana_cost = dynamic_cast<const costs::ManaCost *>(cost))
        {
            auto json = nlohmann::json{{"type", "ManaCost"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["mana"] =
                JsonFactory<mana::Mana>::create_json(mana_cost->getMana());
            return json;
        }
        if ([[maybe_unused]] const auto *self_sacrifice_cost =
                dynamic_cast<const costs::SelfSacrificeCost *>(cost))
        {
            auto json = nlohmann::json{{"type", "SelfSacrificeCost"},
                                       {"data", nlohmann::json::object()}};
            return json;
        }

        throw std::runtime_error("Unknown cost type for JSON serialization: " +
                                 std::string(typeid(*cost).name()));
    }

    std::unique_ptr<costs::ICost> JsonFactory<costs::ICost>::create_product(
        const nlohmann::json &json)
    {
        const auto &type = json.at("type").get<std::string>();
        const auto &data = json.at("data");

        if (type == "CyclingCost")
        {
            const auto &generic_cost_json = data.at("inner_cost");
            auto generic_cost = create_product(generic_cost_json);
            return std::make_unique<costs::CyclingCost>(
                std::move(generic_cost));
        }
        if (type == "ManaCost")
        {
            const auto &mana_json = data.at("mana");
            auto mana = JsonFactory<mana::Mana>::create_product(mana_json);
            return std::make_unique<costs::ManaCost>(std::move(mana));
        }
        if (type == "SelfSacrificeCost")
        {
            return std::make_unique<costs::SelfSacrificeCost>();
        }

        throw std::runtime_error("Unknown cost type for JSON deserialization");
    }
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE