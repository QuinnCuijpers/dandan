#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonAbilityFactory.h"

#include "dandan/dandan.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<abilities::IAbility>::create_json(const IAbility *ability)
    {
        if (const ActivatedAbility *activated = dynamic_cast<const ActivatedAbility *>(ability))
        {
            auto j{
                nlohmann::json{
                    {"type", "ActivatedAbility"},
                    {"data", nlohmann::json::object()}}};
            // TODO: Implement JSON serialization for ActivatedAbility's cost and effect
            // j["data"]["cost"] = create_json(activated->getCost());
            // j["data"]["effect"] = create_json(activated->getEffect());

            return j;
        }
        else if (const ManaAbility *mana = dynamic_cast<const ManaAbility *>(ability))
        {
            auto j =
                nlohmann::json{
                    {"type", "ManaAbility"},
                    {"data", nlohmann::json::object()}};
            j["data"]["color"] = mana->ManaTypeToString(mana->getColor());
            return j;
        }
        else if (const WithDamage *withDamage = dynamic_cast<const WithDamage *>(ability))
        {
            auto j =
                nlohmann::json{
                    {"type", "WithDamage"},
                    {"data", nlohmann::json::object()}};
            j["data"]["damage"] = withDamage->getDamage();
            j["data"]["ability"] = create_json(withDamage->getInnerAbility());
            return j;
        }
        else
        {
            throw std::runtime_error("Unknown ability type for JSON serialization");
        }
    }

    std::unique_ptr<abilities::IAbility> JsonFactory<abilities::IAbility>::create_ability(const nlohmann::json &j)
    {
        const std::string type{j.at("type").get<std::string>()};
        const nlohmann::json &data{j.at("data")};

        if (type == "ActivatedAbility")
        {
            // TODO: Implement JSON deserialization for ActivatedAbility's cost and effect
            throw std::runtime_error("ActivatedAbility deserialization not implemented yet");
        }
        else if (type == "ManaAbility")
        {
            const std::string colorStr{data.at("color").get<std::string>()};
            ManaAbility::ManaType color{ManaAbility::ManaTypeFromString(colorStr)};
            return std::make_unique<ManaAbility>(color);
        }
        else if (type == "WithDamage")
        {
            const int damage{data.at("damage").get<int>()};
            auto inner_ability = create_ability(data.at("ability"));
            return std::make_unique<WithDamage>(std::move(inner_ability), damage);
        }
        else
        {
            throw std::runtime_error("Unknown ability type in JSON: " + type);
        }
    }
}