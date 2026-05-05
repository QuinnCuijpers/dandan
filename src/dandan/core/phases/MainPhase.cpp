#include "dandan/core/phases/MainPhase.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/core/phases/EndingPhase.h"
#include <iterator>

namespace dandan::core
{
    [[nodiscard]] std::unique_ptr<IPhase> MainPhase::handle()
    {
        std::cout << "Handling main phase\n";

        while (true)
        {
            getGame()->render();
            std::cout << "What do you want to do? (play [card index], pass, "
                         "or quit) ";
            std::string input;
            std::getline(std::cin, input);
            if (input == "pass")
            {
                std::cout << "Passing turn\n";
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
                    auto *card{getGame()
                                   ->getActivePlayer()
                                   .getHand()
                                   .getCards()
                                   .at(card_index)
                                   .get()};
                    auto action =
                        std::make_unique<PlayCardAction>(card, getGame());
                    if (getGame()->isActionPrevented(*action))
                    {
                        std::cout << "Action prevented\n";
                        continue;
                    }
                    action->execute();
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