#include "dandan/serialization/JsonCardFactory.h"
#include "dandan/core/CardTypes.h"
#include "dandan/core/ColorWord.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/abilities/IAbility.h"
#include "dandan/core/CardData.h"
#include "dandan/mana/Mana.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{

    nlohmann::json JsonFactory<core::CardData>::create_json(
        const core::CardData *card)
    {
        auto abilities_json = nlohmann::json::array();

        for (const auto &ability : card->abilities)
        {
            nlohmann::json ability_json;
            ability_json =
                JsonFactory<abilities::IAbility>::create_json(ability.get());
            abilities_json.push_back(ability_json);
        }
        nlohmann::json json{};

        json["name"] = card->name;
        json["cost"] =
            JsonFactory<mana::Mana>::create_json(card->mana_cost.get());
        json["type"] = card->type;

        if (card->color != core::ColorWord::Colorless)
        {
            json["color"] = card->color;
        }

        if (!card->subtypes.empty() &&
            card->subtypes != std::vector{core::SubType::None})
        {
            json["subtypes"] = card->subtypes;
        }
        if (card->supertype != core::SuperType::None)
        {
            json["supertype"] = card->supertype;
        }
        auto stats{card->stats};
        if (stats.has_value())
        {
            auto stats_safe{*stats};
            json["stats"] = {{"power", stats_safe.power},
                             {"toughness", stats_safe.toughness}};
        }
        if (!abilities_json.empty())
        {
            json["abilities"] = abilities_json;
        }

        return json;
    }

    std::unique_ptr<core::CardData> JsonFactory<core::CardData>::create_product(
        const nlohmann::json &json)
    {

        auto name = json.at("name").get<std::string>();
        auto cost = JsonFactory<mana::Mana>::create_product(json.at("cost"));
        auto type = json.at("type").get<core::Type>();

        auto subtypes = std::vector<core::SubType>{};
        if (json.contains("subtypes"))
        {
            subtypes = json["subtypes"];
        }

        auto supertype = core::SuperType::None;
        if (json.contains("supertype"))
        {
            supertype = json.at("supertype").get<core::SuperType>();
        }

        auto stats = std::optional<core::Stats>{};
        if (json.contains("stats"))
        {
            auto stats_json = json.at("stats");
            stats = core::Stats{stats_json.at("power").get<int>(),
                                stats_json.at("toughness").get<int>()};
        }

        auto abilities{std::vector<std::unique_ptr<abilities::IAbility>>{}};
        if (json.contains("abilities"))
        {
            for (const auto &ability_json : json.at("abilities"))
            {
                auto ability = JsonFactory<abilities::IAbility>::create_product(
                    ability_json);
                abilities.push_back(std::move(ability));
            }
        }

        auto color{core::ColorWord::Colorless};
        if (json.contains("color"))
        {
            color = json.at("color");
        }

        return std::make_unique<core::CardData>(
            core::CardData{name, std::move(cost), type, subtypes, supertype,
                           std::move(abilities), stats, color});
    }
} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE