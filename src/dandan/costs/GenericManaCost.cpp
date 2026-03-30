#include "dandan/costs/GenericManaCost.h"
#include "dandan/abilities/IAbility.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace dandan::costs
{
    void GenericManaCost::evaluate()
    {
        std::cout << "Evaluating GenericManaCost with " << m_amount << " mana\n";
    }

    // TODO: implemetn from json factory
    void GenericManaCost::from_json(const nlohmann::json &j, ICost &cost)
    {
    }

    void GenericManaCost::to_json(nlohmann::json &j, const ICost &cost)
    {
        const auto &gmc = dynamic_cast<const GenericManaCost &>(cost);
        j = nlohmann::json{{"type", "GernericManaCost"}, {"data", nlohmann::json()}};
        j["data"]["generic_mana_amount"] = gmc.m_amount;
    }
}