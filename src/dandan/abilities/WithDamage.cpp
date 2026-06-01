#include "dandan/abilities/WithDamage.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{

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