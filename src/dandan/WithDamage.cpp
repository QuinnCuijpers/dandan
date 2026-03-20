#include "dandan/WithDamage.h"
#include "dandan/ManaAbility.h"
#include <nlohmann/json.hpp>
#include <iostream>

void WithDamage::resolve()
{
    m_ability->resolve();
    std::cout << "Resolving WithDamage decorator\n";
    std::cout << "Dealing " << m_damage << " damage\n";
}

// TODO: Refactor to use a factory pattern to create abilities based on the "type" field in the JSON
void WithDamage::from_json(const nlohmann::json &j, IAbility &ability)
{
    auto &decorator{dynamic_cast<WithDamage &>(ability)};
    auto &data{j.at("data")};
    decorator.m_damage = data.at("damage").get<int>();
    const auto &ability_json{data.at("ability")};
    const std::string type = ability_json.at("type").get<std::string>();
    std::unique_ptr<IAbility> inner_ability;
    if (type == "ManaAbility")
    {
        inner_ability = std::make_unique<ManaAbility>();
    }
    else if (type == "WithDamage")
    {
        inner_ability = std::make_unique<WithDamage>(nullptr, 0); // Placeholder, will be set in from_json
    }
    else
    {
        throw std::runtime_error("Unknown ability type: " + type);
    }
    inner_ability->from_json(ability_json, *inner_ability);
    decorator.m_ability = std::move(inner_ability);
}

void WithDamage::to_json(nlohmann::json &j, const IAbility &ability)
{
    const auto &decorator{dynamic_cast<const WithDamage &>(ability)};
    j = nlohmann::json{{"type", "WithDamage"}, {"data", nlohmann::json()}};
    j["data"]["damage"] = decorator.m_damage;
    j["data"]["ability"] = nlohmann::json();
    decorator.m_ability->to_json(j["data"]["ability"], *decorator.m_ability);
}