#include "dandan/abilities/WithDamage.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/abilities/EventTriggeredAbility.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{
    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::costs;
    using namespace dandan::mana;

    const auto registered = []
    {
        AbilityRegistry::instance().registerType<WithDamage>(
            "WithDamage",
            [](const IAbility *ability)
            {
                auto json = nlohmann::json::object();
                const auto *with_damage{
                    dynamic_cast<const WithDamage *>(ability)};
                json["damage"] = with_damage->getDamage();
                json["ability"] = JsonFactory<IAbility>::create_json(
                    with_damage->getInnerAbility());
                return json;
            },
            [](const nlohmann::json &json)
            {
                const int damage{json.at("damage").get<int>()};
                auto inner_ability =
                    JsonFactory<IAbility>::create_product(json.at("ability"));
                return std::make_unique<WithDamage>(std::move(inner_ability),
                                                    damage);
            });

        return true;
    }();
} // namespace
#endif

namespace dandan::abilities
{
    WithDamage::WithDamage(std::unique_ptr<IAbility> ability)
        : IAbilityDecorator(std::move(ability)) {};

    WithDamage::WithDamage(std::unique_ptr<IAbility> ability, int damage)
        : IAbilityDecorator(std::move(ability)), m_damage{damage}
    {
    }

    std::string WithDamage::display() const
    {
        std::string res{};
        res += m_ability->display() + ". ";
        res += "This Card deals ";
        res += std::to_string(m_damage);
        res += " damage to you";
        return res;
    }

    std::string WithDamage::displayOption(size_t index) const
    {
        std::string res{};
        res += m_ability->displayOption(index) + ". ";
        res += "This Card deals ";
        res += std::to_string(m_damage);
        res += " damage to you";
        return res;
    }

    [[nodiscard]] int WithDamage::getDamage() const
    {
        return m_damage;
    }

    [[nodiscard]] bool WithDamage::appliesTo(
        const events::IEvent &event, abilities::AbilityContext context) const
    {
        if (const auto *eventTriggeredAbility =
                dynamic_cast<const EventTriggeredAbility *>(m_ability.get()))
        {
            return eventTriggeredAbility->appliesTo(event, std::move(context));
        }
        return false;
    }

    std::unique_ptr<effects::IOneShotEffect> WithDamage::createEffect(
        core::Game &game, AbilityContext context) const
    {
        std::cout << "Resolving WithDamage decorator\n";
        auto player_id{context.controller_id};
        auto &player{game.getPlayer(player_id)};
        player.takeDamage(m_damage, game);
        return m_ability->createEffect(game, context);
    }
} // namespace dandan::abilities
