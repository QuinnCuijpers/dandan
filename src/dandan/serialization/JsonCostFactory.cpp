#include "dandan/serialization/JsonCostFactory.h"
#include "dandan/costs/AndCost.h"
#include "dandan/costs/TapCost.h"
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
        if ([[maybe_unused]] const auto *tap_cost =
                dynamic_cast<const costs::TapCost *>(cost))
        {
            auto json = nlohmann::json{{"type", "TapCost"},
                                       {"data", nlohmann::json::object()}};
            return json;
        }

        if (const auto *andCost = dynamic_cast<const costs::AndCost *>(cost))
        {
            auto json = nlohmann::json{{"type", "AndCost"},
                                       {"data", nlohmann::json::object()}};
            const auto &sub_costs = andCost->getCosts();
            json["data"]["sub_costs"] = nlohmann::json::array();
            for (const auto &sub_cost : sub_costs)
            {
                json["data"]["sub_costs"].push_back(create_json(sub_cost));
            }
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
        if (type == "TapCost")
        {
            return std::make_unique<costs::TapCost>();
        }
        if (type == "AndCost")
        {
            const auto &sub_costs_json = data.at("sub_costs");
            if (!sub_costs_json.is_array() || sub_costs_json.size() != 2)
            {
                throw std::runtime_error(
                    "AndCost JSON must have an array of exactly 2 sub_costs");
            }
            auto first_cost = create_product(sub_costs_json.at(0));
            auto second_cost = create_product(sub_costs_json.at(1));
            return std::make_unique<costs::AndCost>(std::move(first_cost),
                                                    std::move(second_cost));
        }

        throw std::runtime_error("Unknown cost type for JSON deserialization");
    }
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE