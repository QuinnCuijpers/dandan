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
        if (const auto *activated =
                dynamic_cast<const ActivatedAbility *>(ability))
        {
            auto json = nlohmann::json{{"type", "ActivatedAbility"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["cost"] =
                JsonFactory<costs::ICost>::create_json(activated->getCost());
            json["data"]["effect"] = JsonFactory<effects::IEffect>::create_json(
                activated->getEffect());

            return json;
        }

        if (const auto *mana = dynamic_cast<const ManaAbility *>(ability))
        {
            auto json = nlohmann::json{{"type", "ManaAbility"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["mana_list"] =
                JsonFactory<dandan::mana::ManaList>::create_json(
                    mana->getMana());

            return json;
        }

        if (const auto *withDamage = dynamic_cast<const WithDamage *>(ability))
        {
            auto json = nlohmann::json{{"type", "WithDamage"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["damage"] = withDamage->getDamage();
            json["data"]["ability"] =
                create_json(withDamage->getInnerAbility());
            return json;
        }

        if (const auto *staticAbility =
                dynamic_cast<const StaticAbility *>(ability))
        {
            auto json = nlohmann::json{{"type", "StaticAbility"},
                                       {"data", nlohmann::json::object()}};

            json["data"]["on_effect"] =
                JsonFactory<effects::IEffect>::create_json(
                    staticAbility->getOnEffect());
            json["data"]["replacement_effect"] =
                JsonFactory<replacement_effects::IReplacementEffect>::
                    create_json(staticAbility->getReplacementEffect());
            return json;
        }

        if (const auto *triggered =
                dynamic_cast<const TriggeredAbility *>(ability))
        {
            auto json = nlohmann::json{{"type", "TriggeredAbility"},
                                       {"data", nlohmann::json::object()}};

            json["data"]["event"] = JsonFactory<events::IEvent>::create_json(
                triggered->getOnEvent());
            json["data"]["effect"] = JsonFactory<effects::IEffect>::create_json(
                triggered->getEffect());
            return json;
        }

        if (const auto *withAdditionalCost =
                dynamic_cast<const WithAdditionalCost *>(ability))
        {
            auto json = nlohmann::json{{"type", "WithAdditionalCost"},
                                       {"data", nlohmann::json::object()}};

            json["data"]["additional_cost"] =
                JsonFactory<costs::ICost>::create_json(
                    withAdditionalCost->getAdditionalCost());
            json["data"]["ability"] =
                create_json(withAdditionalCost->getInnerAbility());
            return json;
        }

        throw std::runtime_error("Unknown ability type for JSON serialization");
    }

    std::unique_ptr<abilities::IAbility> JsonFactory<
        abilities::IAbility>::create_product(const nlohmann::json &json)
    {
        const std::string type{json.at("type").get<std::string>()};
        const nlohmann::json &data{json.at("data")};

        if (type == "ActivatedAbility")
        {
            auto cost{
                JsonFactory<dandan::ICost>::create_product(data.at("cost"))};

            auto effect{JsonFactory<dandan::IEffect>::create_product(
                data.at("effect"))};

            return std::make_unique<ActivatedAbility>(std::move(cost),
                                                      std::move(effect));
        }

        if (type == "ManaAbility")
        {
            std::unique_ptr<dandan::mana::ManaList> mana_list{
                JsonFactory<dandan::mana::ManaList>::create_product(
                    data.at("mana_list"))};

            return std::make_unique<ManaAbility>(std::move(*mana_list));
        }

        if (type == "WithDamage")
        {
            const int damage{data.at("damage").get<int>()};
            auto inner_ability = create_product(data.at("ability"));
            return std::make_unique<WithDamage>(std::move(inner_ability),
                                                damage);
        }

        if (type == "StaticAbility")
        {
            auto on_effect{JsonFactory<dandan::IEffect>::create_product(
                data.at("on_effect"))};

            auto replacement_effect{
                JsonFactory<dandan::IReplacementEffect>::create_product(
                    data.at("replacement_effect"))};

            return std::make_unique<StaticAbility>(
                std::move(on_effect), std::move(replacement_effect));
        }

        if (type == "TriggeredAbility")
        {
            auto event{
                JsonFactory<dandan::IEvent>::create_product(data.at("event"))};

            auto effect{JsonFactory<dandan::IEffect>::create_product(
                data.at("effect"))};

            return std::make_unique<TriggeredAbility>(std::move(event),
                                                      std::move(effect));
        }

        if (type == "WithAdditionalCost")
        {
            auto additional_cost{JsonFactory<dandan::ICost>::create_product(
                data.at("additional_cost"))};

            auto inner_ability = create_product(data.at("ability"));

            return std::make_unique<WithAdditionalCost>(
                std::move(inner_ability), std::move(additional_cost));
        }

        throw std::runtime_error("Unknown ability type in JSON: " + type);
    }
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE