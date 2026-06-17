#include "dandan/core/PriorityManager.h"
#include "dandan/core/Game.h"
#include "dandan/core/Player.h"
#include "dandan/core/PlayerID.h"
#include <stdexcept>
#include <string>

namespace dandan::core
{
    void PriorityManager::passPriority(core::Game &game)
    {
        m_current_player_with_priority =
            game.getNextPlayerID(m_current_player_with_priority);
        handleStack(game);
        setPriorityToPlayer(m_current_player_with_priority, game);
    }

    void PriorityManager::setPriorityToPlayer(PlayerID player_id,
                                              core::Game &game)
    {
        SBAManager::checkSBAs(game);
        m_current_player_with_priority = player_id;
        if (m_last_acted_player == PlayerID::getInvalidID())
        {
            m_last_acted_player = m_current_player_with_priority;
        }
        auto &player{game.getPlayer(player_id)};
        bool canActivateSomething{player.canActivateSomething(game)};

        // If the stack is empty and we cant activate anything into
        // sorcery speed mode

        if (game.stack().isEmpty() && !canActivateSomething)
        {
            m_current_player_with_priority = game.activePlayer().getID();
            return;
        }

        // TODO: move to correct place
        while (player.canActivateSomething(game))
        {
            // game.render();
            std::cout << "checking priotity actions from player "
                      << player.getName() << '\n';
            std::cout << "What do you want to do? (play [card index], activate "
                         "[card index], pass "
                         "or quit) ";
            std::string input;
            std::getline(game.istream(), input);
            if (input == "pass")
            {
                std::cout << "Passing priority\n";
                passPriority(game);
                return;
            }
            if (input == "quit")
            {
                std::cout << "Quitting game\n";
                throw std::runtime_error("Game quit by user");
            }
            if (input.rfind("play ", 0) == 0)
            {
                m_last_acted_player = m_current_player_with_priority;
                game.handlePlay(input);
                continue;
            }
            if (input.rfind("activate ", 0) == 0)
            {
                m_last_acted_player = m_current_player_with_priority;
                game.handleActivate(input);
                continue;
            }
            throw std::runtime_error(std::string("Unhandled input ") + input +
                                     std::string(" when getting priority and "
                                                 "being able to act"));
        }
        std::cout << "Passsing priority as player " << player.getName()
                  << " has no more priority actions available\n";
        passPriority(game);
    }

    void PriorityManager::handleStack(Game &game)
    {
        if (!game.stack().isEmpty())
        {
            // if after passing the last acting player is the current player
            // then the top of the stack should resolve
            std::cout << "Last acted player: " << m_last_acted_player.id()
                      << '\n';
            std::cout << "Current player with priority: "
                      << m_current_player_with_priority.id() << '\n';
            if (m_last_acted_player == m_current_player_with_priority)
            {
                game.stack().resolveNext(game);
            }
        }
    }
} // namespace dandan::core