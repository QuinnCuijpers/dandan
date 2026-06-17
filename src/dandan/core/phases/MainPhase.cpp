#include "dandan/core/phases/MainPhase.h"
#include "dandan/core/Game.h"
#include "dandan/core/phases/CombatPhase.h"
#include "dandan/core/phases/EndingPhase.h"
#include <string>
#include <utility>

namespace dandan::core
{
    MainPhase::MainPhase(Game &game)
        : IPhase(game), m_next_phase(std::make_unique<CombatPhase>(game))
    {
    }

    MainPhase::MainPhase(Game &game, bool pre_combat)
        : IPhase(game), m_pre_combat_main_phase(pre_combat)
    {
        if (!m_pre_combat_main_phase)
        {
            m_next_phase = std::make_unique<EndingPhase>(game);
        }
        else
        {
            m_next_phase = std::make_unique<CombatPhase>(game);
        }
    }

    [[nodiscard]] std::unique_ptr<IPhase> MainPhase::handle()
    {
        std::cout << "Handling " << name() << '\n';
        game().priorityManager().setPriorityToPlayer(
            game().activePlayer().getID(), game());
        while (true)
        {
            game().render();
            std::cout << "What do you want to do? (play [card index], activate "
                         "[card index], pass, next "
                         "or quit) ";
            std::string input;
            std::getline(game().istream(), input);
            if (input == "pass")
            {
                std::cout << "Passing turn\n";
                game().priorityManager().passPriority(game());
                m_next_phase = std::make_unique<EndingPhase>(game());
                break;
            }
            if (input == "quit")
            {
                std::cout << "Quitting game\n";
                throw std::runtime_error("Game quit by user");
            }
            if (input == "next")
            {
                if (m_pre_combat_main_phase)
                {
                    m_next_phase = std::make_unique<CombatPhase>(game());
                }
                else
                {
                    std::cout << "you can't go back to combat phase\n";
                }
                game().priorityManager().passPriority(game());
                break;
            }
            if (input.rfind("play ", 0) == 0)
            {
                game().handlePlay(input);
                game().priorityManager().setPriorityToPlayer(
                    game().activePlayer().getID(), game());
                continue;
            }
            if (input.rfind("activate ", 0) == 0)
            {
                game().handleActivate(input);
                game().priorityManager().setPriorityToPlayer(
                    game().activePlayer().getID(), game());
                continue;
            }
            // TODO: improve error handling for invalid input
            throw std::invalid_argument(
                "Invalid input: " + (input.empty() ? input : "empty input"));
        }
        return std::move(m_next_phase);
    }

} // namespace dandan::core