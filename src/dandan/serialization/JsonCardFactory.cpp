#include "dandan/serialization/JsonCardFactory.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/mana/Mana.h"
#include "dandan/serialization/JsonFactory.h"
#include <nlohmann/json.hpp>
namespace dandan::core
{
    NLOHMANN_JSON_SERIALIZE_ENUM(CardData::Type, // NOLINT
                                 {{CardData::Type::Land, "Land"},
                                  {CardData::Type::Creature, "Creature"},
                                  {CardData::Type::Sorcery, "Sorcery"},
                                  {CardData::Type::Instant, "Instant"},
                                  {CardData::Type::Enchantment, "Enchantment"},
                                  {CardData::Type::Artifact, "Artifact"},
                                  {CardData::Type::Planeswalker,
                                   "Planeswalker"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(CardData::SubType, // NOLINT
                                 {{CardData::SubType::None, "None"},
                                  {CardData::SubType::Island, "Island"},
                                  {CardData::SubType::Swamp, "Swamp"},
                                  {CardData::SubType::Mountain, "Mountain"},
                                  {CardData::SubType::Forest, "Forest"},
                                  {CardData::SubType::Plains, "Plains"},
                                  {CardData::SubType::Fish, "Fish"}});

} // namespace dandan::core

namespace dandan::serialization
{

    nlohmann::json JsonFactory<core::CardData>::create_json(
        const core::CardData *card)
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
        if (card->getSubType() != core::CardData::SubType::None)
        {
            json["subtype"] = card->getSubType();
        }
        auto stats{card->getStats()};
        if (stats.has_value())
        {
            auto stats_safe{*stats};
            json["stats"] = {{"power", stats_safe.power},
                             {"toughness", stats_safe.toughness}};
        }
        json["abilities"] = abilities_json;

        return json;
    }

    std::unique_ptr<core::CardData> JsonFactory<core::CardData>::create_product(
        const nlohmann::json &json)
    {

        auto name = json.at("name").get<std::string>();
        auto cost = JsonFactory<mana::Mana>::create_product(json.at("cost"));
        auto type = json.at("type").get<core::CardData::Type>();

        auto subtype = core::CardData::SubType::None;
        if (json.contains("subtype"))
        {
            subtype = json.at("subtype").get<core::CardData::SubType>();
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

        return std::make_unique<core::CardData>(name, std::move(cost), type,
                                                subtype, std::move(abilities));
    }
} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE