#include "dandan/serialization/JsonAbilityFactory.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <algorithm>

#ifdef DANDAN_SERIALIZE
#include "dandan/dandan.h"
#include "dandan/effects/continuous/IContinuousEffect.h"
#include "dandan/mana/ManaList.h"
#include "dandan/serialization/JsonFactory.h"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::abilities
{
    NLOHMANN_JSON_SERIALIZE_ENUM( // NOLINT
        StaticAbility::Type,
        {{StaticAbility::Type::CharacteristicDefining,
          "CharacteristicDefining"},
         {StaticAbility::Type::Prevention, "Prevention"},
         {StaticAbility::Type::Replacement, "Replacement"}});
}

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
            json["data"]["effect"] =
                JsonFactory<effects::IOneShotEffectDefinition>::create_json(
                    activated->getEffect());

            return json;
        }

        if (const auto *mana = dynamic_cast<const ManaAbility *>(ability))
        {
            auto json = nlohmann::json{{"type", "ManaAbility"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["cost"] =
                JsonFactory<costs::ICost>::create_json(mana->getCost());
            json["data"]["mana_list"] =
                JsonFactory<dandan::mana::ManaList>::create_json(
                    mana->getManaList());

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

            json["data"]["static_type"] = staticAbility->getType();

            json["data"]["continuous_effect"] =
                JsonFactory<effects::IContinuousEffect>::create_json(
                    staticAbility->getEffect());
            return json;
        }

        if (const auto *triggered =
                dynamic_cast<const EventTriggeredAbility *>(ability))
        {
            auto json = nlohmann::json{{"type", "TriggeredAbility"},
                                       {"data", nlohmann::json::object()}};

            json["data"]["trigger"] =
                JsonFactory<triggers::ITrigger>::create_json(
                    triggered->trigger());
            json["data"]["effect"] =
                JsonFactory<effects::IOneShotEffectDefinition>::create_json(
                    triggered->getEffect());
            json["data"]["kind"] = "event";
            return json;
        }
        if (const auto *stateTriggered =
                dynamic_cast<const StateTriggeredAbility *>(ability))
        {
            auto json = nlohmann::json{{"type", "TriggeredAbility"},
                                       {"data", nlohmann::json::object()}};

            json["data"]["condition"] =
                JsonFactory<conditions::ICondition>::create_json(
                    stateTriggered->condition());
            json["data"]["effect"] =
                JsonFactory<effects::IOneShotEffectDefinition>::create_json(
                    stateTriggered->getEffect());
            json["data"]["kind"] = "state";
            return json;
        }
        if (const auto *spellAbility =
                dynamic_cast<const SpellAbility *>(ability))
        {
            auto json = nlohmann::json{{"type", "SpellAbility"},
                                       {"data", nlohmann::json::object()}};
            auto effect_list = nlohmann::json::array();
            std::transform(
                spellAbility->effects().begin(), spellAbility->effects().end(),
                std::back_inserter(effect_list),
                [](const auto &effect)
                {
                    return JsonFactory<effects::IOneShotEffectDefinition>::
                        create_json(effect.get());
                });
            json["data"]["effect_list"] = effect_list;
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

            auto effect{
                JsonFactory<effects::IOneShotEffectDefinition>::create_product(
                    data.at("effect"))};

            return std::make_unique<ActivatedAbility>(std::move(cost),
                                                      std::move(effect));
        }

        if (type == "ManaAbility")
        {
            std::unique_ptr<dandan::mana::ManaList> mana_list{
                JsonFactory<dandan::mana::ManaList>::create_product(
                    data.at("mana_list"))};
            std::unique_ptr<costs::ICost> cost{
                JsonFactory<costs::ICost>::create_product(data.at("cost"))};
            return std::make_unique<ManaAbility>(std::move(cost),
                                                 std::move(*mana_list));
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
            auto static_type{data.at("static_type").get<StaticAbility::Type>()};

            auto continuous_effect{
                JsonFactory<effects::IContinuousEffect>::create_product(
                    data.at("continuous_effect"))};

            return std::make_unique<StaticAbility>(
                static_type, std::move(continuous_effect));
        }

        if (type == "TriggeredAbility")
        {
            auto kind{data.at("kind").get<std::string>()};
            if (kind == "event")
            {
                auto trigger{
                    JsonFactory<dandan::triggers::ITrigger>::create_product(
                        data.at("trigger"))};

                auto effect{JsonFactory<effects::IOneShotEffectDefinition>::
                                create_product(data.at("effect"))};

                return std::make_unique<EventTriggeredAbility>(
                    std::move(trigger), std::move(effect));
            }

            if (kind == "state")
            {
                auto condition{
                    JsonFactory<dandan::conditions::ICondition>::create_product(
                        data.at("condition"))};

                auto effect{JsonFactory<effects::IOneShotEffectDefinition>::
                                create_product(data.at("effect"))};

                return std::make_unique<StateTriggeredAbility>(
                    std::move(condition), std::move(effect));
            }
        }
        if (type == "SpellAbility")
        {
            std::vector<std::unique_ptr<effects::IOneShotEffectDefinition>>
                effect_list;
            std::transform(
                data.at("effect_list").begin(), data.at("effect_list").end(),
                std::back_inserter(effect_list),
                [](const auto &effect_json)
                {
                    return JsonFactory<effects::IOneShotEffectDefinition>::
                        create_product(effect_json);
                });
            return std::make_unique<SpellAbility>(std::move(effect_list));
        }

        throw std::runtime_error("Unknown ability type in JSON: " + type);
    }
} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE