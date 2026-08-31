#include "dandan/core/PriorityManager.h"
#include "dandan/core/GameState.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/SBAManager.h"
#include <stdexcept>
#include <string>

namespace
{
    dandan::core::PlayerID determineStartingPlayer()
    {
        // Randomize whom is starting player
        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> dist(0,
                                             dandan::core::AMOUNT_PLAYERS - 1);

        int starting_player_index = dist(gen);
        return dandan::core::PlayerID::fromInt(starting_player_index);
    }
} // namespace

namespace dandan::core
{
    PriorityManager::PriorityManager()
        : m_current_player_with_priority(determineStartingPlayer())
    {
    }

    void PriorityManager::passPriority(core::ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};

        auto next{game.getNextPlayerID(m_current_player_with_priority)};
        if (!game.stack().isEmpty() && next == m_last_acted_player)
        {
            game.stack().resolveNext(exec_ctx);
        }
        m_current_player_with_priority = next;
        setPriorityToPlayer(next, exec_ctx);
    }

    void PriorityManager::setPriorityToPlayer(PlayerID player_id,
                                              core::ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        SBAManager::checkSBAs(exec_ctx);
        m_current_player_with_priority = player_id;
        if (m_last_acted_player == PlayerID::getInvalidID())
        {
            m_last_acted_player = m_current_player_with_priority;
        }
        auto &player{game.getPlayer(player_id)};
        bool canActivateSomething{player.canActivateSomething(exec_ctx)};

        // If the stack is empty and we cant activate anything into
        // sorcery speed mode

        if (game.stack().isEmpty() &&
            m_current_player_with_priority == game.activePlayer().getID())
        {
            m_last_acted_player = PlayerID::getInvalidID();
            return;
        }

        if (game.stack().isEmpty() && !canActivateSomething)
        {
            m_current_player_with_priority = game.activePlayer().getID();
            m_last_acted_player = PlayerID::getInvalidID();
            return;
        }

        // TODO: move to correct place
        while (player.canActivateSomething(exec_ctx))
        {
            // game.render();
            std::cout << "checking priotity actions from player "
                      << player.getName() << '\n';
            std::cout << "What do you want to do? (play [card index], activate "
                         "[card index], pass "
                         "or quit) ";
            std::string input;
            std::getline(istream, input);
            if (input == "pass")
            {
                std::cout << "Passing priority\n";
                passPriority(exec_ctx);
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
                dandan::core::GameState::handlePlay(input, exec_ctx);
                continue;
            }
            if (input.rfind("activate ", 0) == 0)
            {
                m_last_acted_player = m_current_player_with_priority;
                std::cout
                    << "handling activate for player: "
                    << game.getPlayer(m_current_player_with_priority).getName()
                    << '\n';
                dandan::core::GameState::handleActivate(input, exec_ctx);
                continue;
            }
            throw std::runtime_error(std::string("Unhandled input ") + input +
                                     std::string(" when getting priority and "
                                                 "being able to act"));
        }
        std::cout << "Passsing priority as player " << player.getName()
                  << " has no more priority actions available\n";
        passPriority(exec_ctx);
    }
} // namespace dandan::core
