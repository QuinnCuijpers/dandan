#include "dandan/core/phases/MainPhase.h"
#include "dandan/core/Game.h"
#include "dandan/core/phases/EndingPhase.h"
#include <iterator>

namespace dandan::core
{
    [[nodiscard]] std::unique_ptr<IPhase> MainPhase::handle()
    {
        std::cout << "Handling main phase\n";
        std::cout << "Active player: " << getGame()->getActivePlayer().getName()
                  << '\n';

        std::cout << "Cards in hand:\n";
        for (const auto &card :
             getGame()->getActivePlayer().getHand().getCards())
        {
            std::cout << *card << '\n';
        }

        while (true)
        {
            std::cout
                << "What do you want to do? (play [card index], end phase, "
                   "or quit) ";
            std::string input;
            std::getline(std::cin, input);
            if (input == "end phase")
            {
                std::cout << "Ending main phase\n";
                return std::make_unique<EndingPhase>(getGame());
            }
            if (input == "quit")
            {
                std::cout << "Quitting game\n";
                exit(0);
            }
            else if (input.rfind("play ", 0) == 0)
            {
                try
                {
                    int card_index =
                        std::stoi(input.substr(std::size("play ") - 1));
                    getGame()->getActivePlayer().playCard(card_index);
                }
                catch (const std::exception &e)
                {
                    std::cout << "Invalid input: " << e.what() << '\n';
                }
            }
        }
        // TODO: change to next phase
        return nullptr;
    }
} // namespace dandan::core