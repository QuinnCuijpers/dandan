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
    j = nlohmann::json{{"WithDamage", nlohmann::json()}};
    j["WithDamage"]["damage"] = m_damage;
    j["WithDamage"]["ability"] = nlohmann::json();
    decorator.m_ability->to_json(j["WithDamage"]["ability"], *decorator.m_ability);
}