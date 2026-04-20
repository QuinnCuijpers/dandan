#include "dandan/core/Card.h"

#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include <fstream>
#include <nlohmann/json.hpp>
#endif
namespace dandan::core
{
#ifdef DANDAN_BUILD_SERIALIZE

    Card::Card(std::string_view name) : m_name(name)
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
        *this = std::move(*dandan::serialization::JsonFactory<
                          dandan::core::Card>::create_product(json));
    }

    void from_json(const nlohmann::json &json, Card &card)
    {
        card = std::move(*dandan::serialization::JsonFactory<
                         dandan::core::Card>::create_product(json));
    }

    void to_json(nlohmann::json &json, const Card &card)
    {
        json =
            dandan::serialization::JsonFactory<dandan::core::Card>::create_json(
                &card);
    }
#endif

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