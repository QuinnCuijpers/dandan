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
            auto starting_player_id{game.activePlayer().getID()};
            auto current_player_id{starting_player_id};

            while (true)
            {
                auto &player{game.getPlayer(current_player_id)};
                std::cout << player.getName()
                          << ", how many cards do you want to draw (0-"
                          << m_amount << ")?\n";

                std::string input;
                std::getline(game.istream(), input);
                int draw_amount{std::stoi(input)};

                auto def{dandan::effects::DrawEffectDefinition(draw_amount)};
                auto context{EffectContext{player.getID()}};
                auto effect{def.bind(game, context)};
                effect->apply(game);

                current_player_id = game.getNextPlayerID(current_player_id);
                if (current_player_id == starting_player_id)
                {
                    break;
                }
            }
        }
        else
        {
            game.activePlayer().drawCard(game);
        }
        return nullptr;
    }
} // namespace dandan::effects