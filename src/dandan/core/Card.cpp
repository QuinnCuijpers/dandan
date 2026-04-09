#include "dandan/core/Card.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/serialization/JsonAbilityFactory.h"
#include <nlohmann/json.hpp>
namespace dandan::core
{
    NLOHMANN_JSON_SERIALIZE_ENUM(Card::Type,
                                 {{Card::Type::Land, "Land"},
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

        auto factory{dandan::serialization::JsonFactory<abilities::IAbility>{}};
        for (const auto &ability_json : j.at("abilities"))
        {
            auto ability = factory.create_product(ability_json);
            c.m_abilities.push_back(std::move(ability));
        }
    }

    void to_json(nlohmann::json &j, const Card &c)
    {
        dandan::serialization::JsonFactory<abilities::IAbility> abilityFactory;
        auto ability_json = nlohmann::json::array();
        for (const auto &ability : c.m_abilities)
        {
            nlohmann::json a;
            a = abilityFactory.create_json(ability.get());
            ability_json.push_back(a);
        }
        j = nlohmann::json{{"name", c.m_name},
                           {"cost", c.m_cost},
                           {"type", c.m_type},
                           {"abilities", ability_json}};
    }

    std::string_view Card::TypeToString(Type type)
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
} // namespace dandan::core