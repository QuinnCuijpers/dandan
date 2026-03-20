#include "dandan/WithDamage.h"
#include <nlohmann/json.hpp>
#include <iostream>

void WithDamage::resolve()
{
    m_ability->resolve();
    std::cout << "Resolving WithDamage decorator\n";
    std::cout << "Dealing " << m_damage << " damage\n";
}

void WithDamage::to_json(nlohmann::json &j, const IAbility &ability)
{
    const auto &decorator{dynamic_cast<const WithDamage &>(ability)};
    j = nlohmann::json{{"type", "WithDamage"}, {"data", nlohmann::json()}};
    j["data"]["damage"] = decorator.m_damage;
    j["data"]["ability"] = nlohmann::json();
    decorator.m_ability->to_json(j["data"]["ability"], *decorator.m_ability);
}