#include "dandan/abilities/WithDamage.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/abilities/EventTriggeredAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

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
