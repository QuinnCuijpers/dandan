#include "dandan/serialization/JsonCardFactory.h"

#ifdef DANDAN_BUILD_SERIALIZE
#include <nlohmann/json.hpp>
namespace dandan::core
{
    NLOHMANN_JSON_SERIALIZE_ENUM(Card::Type, // NOLINT
                                 {{Card::Type::Land, "Land"},
                                  {Card::Type::Creature, "Creature"},
                                  {Card::Type::Sorcery, "Sorcery"},
                                  {Card::Type::Instant, "Instant"},
                                  {Card::Type::Enchantment, "Enchantment"},
                                  {Card::Type::Artifact, "Artifact"},
                                  {Card::Type::Planeswalker, "Planeswalker"}});

} // namespace dandan::core

namespace dandan::serialization
{

    nlohmann::json JsonFactory<core::Card>::create_json(const core::Card *card)
    {
        auto ability_json = nlohmann::json::array();

        for (const auto &ability : card->getAbilities())
        {
            nlohmann::json ability_json;
            ability_json =
                JsonFactory<abilities::IAbility>::create_json(ability.get());
            ability_json.push_back(ability_json);
        }
        nlohmann::json json{};

        json["name"] = card->getName();
        json["cost"] = card->getCost();
        json["type"] = card->getType();
        json["abilities"] = ability_json;

        return json;
    }

    std::unique_ptr<core::Card> JsonFactory<core::Card>::create_product(
        const nlohmann::json &json)
    {

        auto name = json.at("name").get<std::string>();
        int cost{};
        if (json.at("cost").is_string())
        {
            cost = std::stoi(json.at("cost").get<std::string>());
        }
        else
        {
            cost = json.at("cost").get<int>();
        }
        auto type = json.at("type").get<core::Card::Type>();

        auto abilities{std::vector<std::unique_ptr<abilities::IAbility>>{}};
        for (const auto &ability_json : json.at("abilities"))
        {
            auto ability =
                JsonFactory<abilities::IAbility>::create_product(ability_json);
            abilities.push_back(std::move(ability));
        }

        return std::make_unique<core::Card>(name, cost, type,
                                            std::move(abilities));
    }
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE