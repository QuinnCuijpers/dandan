#include "dandan/serialization/JsonCardFactory.h"

#ifdef DANDAN_BUILD_SERIALIZE
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
                                  {Card::Type::Planeswalker, "Planeswalker"}});

} // namespace dandan::core

namespace dandan::serialization
{

    nlohmann::json JsonFactory<core::Card>::create_json(const core::Card *card)
    {
        dandan::serialization::JsonFactory<abilities::IAbility> abilityFactory;
        auto ability_json = nlohmann::json::array();

        for (const auto &ability : card->getAbilities())
        {
            nlohmann::json a;
            a = abilityFactory.create_json(ability.get());
            ability_json.push_back(a);
        }
        nlohmann::json j{};

        j["name"] = card->getName();
        j["cost"] = card->getCost();
        j["type"] = card->getType();
        j["abilities"] = ability_json;

        return j;
    }

    std::unique_ptr<core::Card> JsonFactory<core::Card>::create_product(
        const nlohmann::json &j)
    {

        auto name = j.at("name").get<std::string>();
        int cost{};
        if (j.at("cost").is_string())
        {
            cost = std::stoi(j.at("cost").get<std::string>());
        }
        else
        {
            cost = j.at("cost").get<int>();
        }
        auto type = j.at("type").get<core::Card::Type>();

        auto factory{dandan::serialization::JsonFactory<abilities::IAbility>{}};
        auto abilities{std::vector<std::unique_ptr<abilities::IAbility>>{}};
        for (const auto &ability_json : j.at("abilities"))
        {
            auto ability = factory.create_product(ability_json);
            abilities.push_back(std::move(ability));
        }

        return std::make_unique<core::Card>(name, cost, type,
                                            std::move(abilities));
    }
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE