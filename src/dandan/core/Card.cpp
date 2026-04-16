#include "dandan/core/Card.h"
#include "dandan/serialization/JsonFactory.h"

#ifdef DANDAN_BUILD_SERIALIZE
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
        nlohmann::json j;
        file >> j;
        auto factory{dandan::serialization::JsonFactory<Card>{}};
        *this = std::move(*factory.create_product(j));
    }

    void from_json(const nlohmann::json &j, Card &c)
    {
        auto factory{dandan::serialization::JsonFactory<core::Card>()};
        c = std::move(*factory.create_product(j));
    }

    void to_json(nlohmann::json &j, const Card &c)
    {
        auto factory{dandan::serialization::JsonFactory<core::Card>()};
        j = factory.create_json(&c);
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