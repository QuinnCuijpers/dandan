#include "dandan/Card.h"

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
    c.m_cost = j.at("cost").get<int>();
    c.m_type = j.at("type").get<Card::Type>();
}
void to_json(nlohmann::json &j, const Card &c)
{
    j = nlohmann::json{{"name", c.m_name}, {"cost", c.m_cost}, {"type", c.m_type}};
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