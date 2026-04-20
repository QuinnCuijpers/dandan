#include "dandan/serialization/JsonAbilityFactory.h"

#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/dandan.h"
#include "dandan/mana/ManaList.h"
#include "dandan/serialization/JsonFactory.h"
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
            j["data"]["mana_list"] =
                JsonFactory<dandan::mana::ManaList>::create_json(
                    mana->getMana());

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
        else if (const StaticAbility *staticAbility =
                     dynamic_cast<const StaticAbility *>(ability))
        {
            auto j = nlohmann::json{{"type", "StaticAbility"},
                                    {"data", nlohmann::json::object()}};

            j["data"]["on_effect"] = JsonFactory<effects::IEffect>::create_json(
                staticAbility->getOnEffect());
            j["data"]["replacement_effect"] =
                JsonFactory<replacement_effects::IReplacementEffect>::
                    create_json(staticAbility->getReplacementEffect());
            return j;
        }
        else if (const TriggeredAbility *triggered =
                     dynamic_cast<const TriggeredAbility *>(ability))
        {
            auto j = nlohmann::json{{"type", "TriggeredAbility"},
                                    {"data", nlohmann::json::object()}};

            j["data"]["event"] = JsonFactory<events::IEvent>::create_json(
                triggered->getOnEvent());
            j["data"]["effect"] = JsonFactory<effects::IEffect>::create_json(
                triggered->getEffect());
            return j;
        }
        else if (const auto *withAdditionalCost =
                     dynamic_cast<const WithAdditionalCost *>(ability))
        {
            auto j = nlohmann::json{{"type", "WithAdditionalCost"},
                                    {"data", nlohmann::json::object()}};

            j["data"]["additional_cost"] =
                JsonFactory<costs::ICost>::create_json(
                    withAdditionalCost->getAdditionalCost());
            j["data"]["ability"] =
                create_json(withAdditionalCost->getInnerAbility());
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
            std::unique_ptr<dandan::mana::ManaList> mana_list{
                JsonFactory<dandan::mana::ManaList>::create_product(
                    data.at("mana_list"))};

            return std::make_unique<ManaAbility>(std::move(*mana_list));
        }
        else if (type == "WithDamage")
        {
            const int damage{data.at("damage").get<int>()};
            auto inner_ability = create_product(data.at("ability"));
            return std::make_unique<WithDamage>(std::move(inner_ability),
                                                damage);
        }
        else if (type == "StaticAbility")
        {
            auto on_effect{JsonFactory<dandan::IEffect>::create_product(
                data.at("on_effect"))};

            auto replacement_effect{
                JsonFactory<dandan::IReplacementEffect>::create_product(
                    data.at("replacement_effect"))};

            return std::make_unique<StaticAbility>(
                std::move(on_effect), std::move(replacement_effect));
        }
        else if (type == "TriggeredAbility")
        {
            auto event{
                JsonFactory<dandan::IEvent>::create_product(data.at("event"))};

            auto effect{JsonFactory<dandan::IEffect>::create_product(
                data.at("effect"))};

            return std::make_unique<TriggeredAbility>(std::move(event),
                                                      std::move(effect));
        }
        else if (type == "WithAdditionalCost")
        {
            auto additional_cost{JsonFactory<dandan::ICost>::create_product(
                data.at("additional_cost"))};

            auto inner_ability = create_product(data.at("ability"));

            return std::make_unique<WithAdditionalCost>(
                std::move(inner_ability), std::move(additional_cost));
        }
        else
        {
            throw std::runtime_error("Unknown ability type in JSON: " + type);
        }
    }
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE