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
            game().render();
            std::cout << "What do you want to do? (play [card index], pass, "
                         "or quit) ";
            std::string input;
            std::getline(game().istream(), input);
            if (input == "pass")
            {
                std::cout << "Passing turn\n";
                return std::make_unique<EndingPhase>(game());
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
                    auto card{game().activePlayer().hand().getCard(card_index)};
                    auto action =
                        std::make_unique<PlayCardAction>(card, game());
                    if (game().isActionPrevented(*action))
                    {
                        std::cout << "Action prevented\n";
                        continue;
                    }
                    auto effect{action->createEffect()};
                    // should add to stack and resolve later, but for now just
                    // apply immediately as we only have cards
                    auto event{effect->apply(game())};
                    game().eventManager().notify(*event, game());
                }
                catch (const std::exception &e)
                {
                    std::cout << "Invalid input: " << e.what() << '\n';
                }
            }
        }
        // TODO: change to next phase which would be combat phase normally
        return nullptr;
    }
} // namespace dandan::core