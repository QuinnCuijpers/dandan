#include "dandan/core/CardData.h"
#include "dandan/abilities/IAbility.h"
#include <cassert>
#include <memory>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include <fstream>
#include <nlohmann/json.hpp>
#endif
namespace dandan::core
{
#ifdef DANDAN_SERIALIZE

    CardData::CardData(std::string_view name)
    {
        auto json_path{std::filesystem::path(DANDAN_PROJECT_SOURCE) /
                       "data/jsons" / (std::string(name) + ".json")};
        std::ifstream file{json_path};
        if (!file)
        {
            std::cerr << "Failed to open JSON file for card: " << name << '\n';
            return;
        }
        nlohmann::json json;
        file >> json;
        *this = json.get<CardData>();
    }

    void from_json(const nlohmann::json &json, CardData &card)
    {
        card = std::move(*dandan::serialization::JsonFactory<
                         dandan::core::CardData>::create_product(json));
    }

    void to_json(nlohmann::json &json, const CardData &card)
    {
        json = dandan::serialization::JsonFactory<
            dandan::core::CardData>::create_json(&card);
    }
#endif
    CardData::CardData(
        std::string_view name, std::unique_ptr<mana::Mana> cost, Type type,
        SubType subtype, SuperType supertype,
        std::vector<std::unique_ptr<abilities::IAbility>> abilities,
        std::optional<Stats> stats)
        : m_name{name}, m_mana_cost{std::move(cost)}, m_type{type},
          m_subtype{subtype}, m_supertype{supertype},
          m_abilities{std::move(abilities)}, m_stats{stats}
    {
    }

    void CardData::addAbility(std::unique_ptr<abilities::IAbility> ability)
    {
        m_abilities.push_back(std::move(ability));
    }

    std::string_view CardData::TypeToString(Type type)
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
        }
        assert(false && "Unreachable Card type");
    }

    std::string_view CardData::SubTypeToString(SubType subtype)
    {
        switch (subtype)
        {
        case SubType::None:
            return "None";
        case SubType::Forest:
            return "Forest";
        case SubType::Island:
            return "Island";
        case SubType::Mountain:
            return "Mountain";
        case SubType::Plains:
            return "Plains";
        case SubType::Swamp:
            return "Swamp";
        case SubType::Fish:
            return "Fish";
        }
        assert(false && "Unreachable Card subtype");
    }
} // namespace dandan::core