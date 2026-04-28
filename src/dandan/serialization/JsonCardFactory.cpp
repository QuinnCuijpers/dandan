#include "dandan/serialization/JsonCardFactory.h"
#include "dandan/mana/Mana.h"
#include "dandan/serialization/JsonFactory.h"

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

    NLOHMANN_JSON_SERIALIZE_ENUM(Card::SubType, // NOLINT
                                 {{Card::SubType::None, "None"},
                                  {Card::SubType::Island, "Island"},
                                  {Card::SubType::Swamp, "Swamp"},
                                  {Card::SubType::Mountain, "Mountain"},
                                  {Card::SubType::Forest, "Forest"},
                                  {Card::SubType::Plains, "Plains"},
                                  {Card::SubType::Fish, "Fish"}});

} // namespace dandan::core

namespace dandan::serialization
{

    nlohmann::json JsonFactory<core::Card>::create_json(const core::Card *card)
    {
        auto abilities_json = nlohmann::json::array();

        for (const auto &ability : card->getAbilities())
        {
            nlohmann::json ability_json;
            ability_json =
                JsonFactory<abilities::IAbility>::create_json(ability.get());
            abilities_json.push_back(ability_json);
        }
        nlohmann::json json{};

        json["name"] = card->getName();
        json["cost"] = JsonFactory<mana::Mana>::create_json(card->getCost());
        json["type"] = card->getType();
        if (card->getSubType() != core::Card::SubType::None)
        {
            json["subtype"] = card->getSubType();
        }
        if (card->getStats().has_value())
        {
            json["stats"] = {{"power", card->getStats()->power},
                             {"toughness", card->getStats()->toughness}};
        }
        json["abilities"] = abilities_json;

        return json;
    }

    std::unique_ptr<core::Card> JsonFactory<core::Card>::create_product(
        const nlohmann::json &json)
    {

        auto name = json.at("name").get<std::string>();
        auto cost = JsonFactory<mana::Mana>::create_product(json.at("cost"));
        auto type = json.at("type").get<core::Card::Type>();

        auto subtype = core::Card::SubType::None;
        if (json.contains("subtype"))
        {
            subtype = json.at("subtype").get<core::Card::SubType>();
        }

        auto stats = std::optional<core::Stats>{};
        if (json.contains("stats"))
        {
            auto stats_json = json.at("stats");
            stats = core::Stats{stats_json.at("power").get<int>(),
                                stats_json.at("toughness").get<int>()};
        }

        auto abilities{std::vector<std::unique_ptr<abilities::IAbility>>{}};
        for (const auto &ability_json : json.at("abilities"))
        {
            auto ability =
                JsonFactory<abilities::IAbility>::create_product(ability_json);
            abilities.push_back(std::move(ability));
        }

        return std::make_unique<core::Card>(name, std::move(cost), type,
                                            subtype, std::move(abilities));
    }
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE