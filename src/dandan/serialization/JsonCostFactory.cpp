#include "dandan/serialization/JsonCostFactory.h"
#include "dandan/costs/CyclingCost.h"
#include "dandan/costs/ICost.h"
#include "dandan/costs/ManaCost.h"
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
            auto j = nlohmann::json{{"type", "CyclingCost"},
                                    {"data", nlohmann::json::object()}};

            const auto inner_cost = cycle_cost->getInnerCost();
            j["data"]["inner_cost"] = create_json(inner_cost);
            return j;
        }
        else if (const auto *mana_cost =
                     dynamic_cast<const costs::ManaCost *>(cost))
        {
            auto j = nlohmann::json{{"type", "ManaCost"},
                                    {"data", nlohmann::json::object()}};
            j["data"]["mana"] =
                JsonFactory<mana::Mana>::create_json(mana_cost->getMana());
            return j;
        }
        else
        {
            throw std::runtime_error(
                "Unknown cost type for JSON serialization: " +
                std::string(typeid(*cost).name()));
        }
    }

    std::unique_ptr<costs::ICost> JsonFactory<costs::ICost>::create_product(
        const nlohmann::json &j)
    {
        const auto &type = j.at("type").get<std::string>();
        const auto &data = j.at("data");

        if (type == "CyclingCost")
        {
            auto generic_cost_json = data.at("inner_cost");
            auto generic_cost = create_product(generic_cost_json);
            return std::make_unique<costs::CyclingCost>(
                std::move(generic_cost));
        }
        else if (type == "ManaCost")
        {
            auto mana_json = data.at("mana");
            auto mana = JsonFactory<mana::Mana>::create_product(mana_json);
            return std::make_unique<costs::ManaCost>(std::move(mana));
        }
        else
        {
            throw std::runtime_error(
                "Unknown cost type for JSON deserialization");
        }
    }
} // namespace dandan::serialization