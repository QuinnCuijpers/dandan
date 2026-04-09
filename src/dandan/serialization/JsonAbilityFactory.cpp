#include "dandan/serialization/JsonAbilityFactory.h"
#include "dandan/serialization/JsonFactory.h"

#include "dandan/dandan.h"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<abilities::IAbility>::create_json(
        const IAbility *ability)
    {
        if (const ActivatedAbility *activated =
                dynamic_cast<const ActivatedAbility *>(ability))
        {
            auto j = nlohmann::json{{"type", "ActivatedAbility"},
                                    {"data", nlohmann::json::object()}};
            j["data"]["cost"] =
                JsonFactory<costs::ICost>::create_json(activated->getCost());
            j["data"]["effect"] = JsonFactory<effects::IEffect>::create_json(
                activated->getEffect());

            return j;
        }
        else if (const ManaAbility *mana =
                     dynamic_cast<const ManaAbility *>(ability))
        {
            auto j = nlohmann::json{{"type", "ManaAbility"},
                                    {"data", nlohmann::json::object()}};
            j["data"]["color"] = mana->ManaTypeToString(mana->getColor());
            return j;
        }
        else if (const WithDamage *withDamage =
                     dynamic_cast<const WithDamage *>(ability))
        {
            auto j = nlohmann::json{{"type", "WithDamage"},
                                    {"data", nlohmann::json::object()}};
            j["data"]["damage"] = withDamage->getDamage();
            j["data"]["ability"] = create_json(withDamage->getInnerAbility());
            return j;
        }
        else if (const ReplacementAbility *replacement =
                     dynamic_cast<const ReplacementAbility *>(ability))
        {
            auto j = nlohmann::json{{"type", "ReplacementAbility"},
                                    {"data", nlohmann::json::object()}};

            j["data"]["event"] = JsonFactory<events::IEvent>::create_json(
                replacement->getEvent());
            j["data"]["replace_effect"] =
                JsonFactory<effects::IReplacementEffect>::create_json(
                    replacement->getReplaceEffect());
            return j;
        }
        else
        {
            throw std::runtime_error(
                "Unknown ability type for JSON serialization");
        }
    }

    std::unique_ptr<abilities::IAbility> JsonFactory<
        abilities::IAbility>::create_product(const nlohmann::json &j)
    {
        const std::string type{j.at("type").get<std::string>()};
        const nlohmann::json &data{j.at("data")};

        if (type == "ActivatedAbility")
        {
            auto cost{
                JsonFactory<dandan::ICost>::create_product(data.at("cost"))};

            auto effect{JsonFactory<dandan::IEffect>::create_product(
                data.at("effect"))};

            return std::make_unique<ActivatedAbility>(std::move(cost),
                                                      std::move(effect));
        }
        else if (type == "ManaAbility")
        {
            const std::string colorStr{data.at("color").get<std::string>()};
            ManaAbility::ManaType color{
                ManaAbility::ManaTypeFromString(colorStr)};
            return std::make_unique<ManaAbility>(color);
        }
        else if (type == "WithDamage")
        {
            const int damage{data.at("damage").get<int>()};
            auto inner_ability = create_product(data.at("ability"));
            return std::make_unique<WithDamage>(std::move(inner_ability),
                                                damage);
        }
        else if (type == "ReplacementAbility")
        {
            auto event{
                JsonFactory<dandan::IEvent>::create_product(data.at("event"))};

            auto effect{JsonFactory<dandan::IReplacementEffect>::create_product(
                data.at("replace_effect"))};

            return std::make_unique<ReplacementAbility>(std::move(event),
                                                        std::move(effect));
        }
        else
        {
            throw std::runtime_error("Unknown ability type in JSON: " + type);
        }
    }
} // namespace dandan::serialization