#include "dandan/effects/one_shot/OptionalDrawEffect.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include <string>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> OptionalDrawEffect::apply_impl(
        core::Game &game) const
    {
        if (m_each_player)
        {
            // TODO: need to have draweffect take a player
            for (auto &player : game.getPlayers())
            {
                std::cout << player.getName()
                          << ", how many cards do you want to draw (0-"
                          << m_amount << ")?\n";
                std::string input;
                std::getline(game.istream(), input);
                int draw_amount{std::stoi(input)};

                auto def{dandan::effects::DrawEffectDefinition(draw_amount)};
                auto context{EffectContext{player.getID()}};
                auto effect{def.bind(context)};
                effect->apply(game);
            }
        }
        else
        {
            game.activePlayer().drawCard(game);
        }
        return nullptr;
    }
} // namespace dandan::effects