#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonCostFactory.h"
#include "dandan/costs/ICost.h"
#include "dandan/costs/CyclingCost.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<costs::ICost>::create_json(const costs::ICost *cost)
    {
        if (const auto *cycle_cost = dynamic_cast<const costs::CyclingCost *>(cost))
        {
            auto j =
                nlohmann::json{
                    {"type", "CyclingCost"},
                    {"data", nlohmann::json::object()}};

            auto generic_cost{cycle_cost->getGenericAmount()};
            j["data"]["generic_mana_cost"] = create_json(&generic_cost);
            return j;
        }
        else
        {
            throw std::runtime_error("Unknown cost type for JSON serialization");
        }
    }
}