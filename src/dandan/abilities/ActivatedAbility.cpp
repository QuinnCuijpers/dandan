#include "dandan/abilities/ActivatedAbility.h"
#include <iostream>
#include <nlohmann/json.hpp>

namespace dandan::abilities
{
    void ActivatedAbility::resolve()
    {
        std::cout << "Resolving Activated ability\n";
        m_cost->evaluate();
        m_effect->apply();
    }

    void ActivatedAbility::from_json(const nlohmann::json &j, IAbility &ability)
    {
    }

    void ActivatedAbility::to_json(nlohmann::json &j, const IAbility &ability)
    {

        const auto &replacementAbility = dynamic_cast<const ActivatedAbility &>(ability);
        j = nlohmann::json{{"type", "ReplacementAbility"}, {"data", nlohmann::json()}};

        j["data"]["cost"] = nlohmann::json();
        replacementAbility.m_cost->to_json(j["data"]["cost"], *replacementAbility.m_cost);

        j["data"]["effect"] = nlohmann::json();
        replacementAbility.m_effect->to_json(j["data"]["effect"], *replacementAbility.m_effect);
    }
}