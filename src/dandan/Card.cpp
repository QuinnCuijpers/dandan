#include "dandan/Card.h"
#include "dandan/IAbility.h"
#include <nlohmann/json.hpp>

NLOHMANN_JSON_SERIALIZE_ENUM(Card::Type, {{Card::Type::Land, "Land"},
                                          {Card::Type::Creature, "Creature"},
                                          {Card::Type::Sorcery, "Sorcery"},
                                          {Card::Type::Instant, "Instant"},
                                          {Card::Type::Enchantment, "Enchantment"},
                                          {Card::Type::Artifact, "Artifact"},
                                          {Card::Type::Planeswalker, "Planeswalker"}})

void from_json(const nlohmann::json &j, Card &c)
{
    c.m_name = j.at("name").get<std::string>();
    if (j.at("cost").is_string())
    {
        c.m_cost = std::stoi(j.at("cost").get<std::string>());
    }
    else
    {
        c.m_cost = j.at("cost").get<int>();
    }
    c.m_type = j.at("type").get<Card::Type>();
}
void to_json(nlohmann::json &j, const Card &c)
{
    j = nlohmann::json{{"name", c.m_name}, {"cost", c.m_cost}, {"type", c.m_type}, {"effects", nlohmann::json::array()}};
    for (const auto &ability : c.m_abilities)
    {
        nlohmann::json a;
        ability.get()->to_json(a, *ability.get());
        j["effects"].push_back(a);
    }
}

std::string_view Card::TypeToString(Type type) const
{
    switch (type)
    {
    case Type::Land:
        return "Land";
    case Type::Creature:
        return "Creature";
    case Type::Sorcery:
        return "Sorcery";
    case Type::Instant:
        return "Instant";
    case Type::Enchantment:
        return "Enchantment";
    case Type::Artifact:
        return "Artifact";
    case Type::Planeswalker:
        return "Planeswalker";
    default:
        return "Unknown";
    }
}