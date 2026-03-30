#include "dandan/costs/CyclingCost.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace dandan::costs
{
    void CyclingCost::evaluate()
    {
        std::cout << "Evaluating CyclingCost\n";
        m_generic_mana_cost.evaluate();
    }
    void CyclingCost::from_json(const nlohmann::json &j, ICost &cost)
    {
    }

    void CyclingCost::to_json(nlohmann::json &j, const ICost &cost)
    {
        const auto &cycling_cost{dynamic_cast<const CyclingCost &>(cost)};
        j = nlohmann::json{{"type", "CyclingCost"}, {"data", nlohmann::json{}}};

        j["data"]["generic_mana_cost"] = nlohmann::json{};
        auto generic_mana_cost = cycling_cost.getGenericAmount();
        generic_mana_cost.to_json(j["data"]["generic_mana_cost"], generic_mana_cost);
    }
}