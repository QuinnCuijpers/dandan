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
            std::cout
                << "What do you want to do? (play [card index], pass, combat "
                   "or quit) ";
            std::string input;
            std::getline(game().istream(), input);
            if (input == "pass")
            {
                std::cout << "Passing turn\n";
                m_next_phase = std::make_unique<EndingPhase>(game());
                break;
            }
            if (input == "quit")
            {
                std::cout << "Quitting game\n";
                exit(0);
            }
            if (input == "combat")
            {
                m_next_phase = std::make_unique<CombatPhase>(game());
                break;
            }
            if (input.rfind("play ", 0) == 0)
            {
                try
                {
                    int card_index =
                        std::stoi(input.substr(std::size("play ") - 1));
                    // moves card out of hand
                    auto card{game().activePlayer().hand().getCard(card_index)};
                    auto action =
                        std::make_unique<PlayCardAction>(card, game());
                    if (game().isActionPrevented(*action))
                    {
                        std::cout << "Action prevented\n";
                        // return card to hand since action was prevented
                        game().activePlayer().hand().insertAt(card_index, card);
                        continue;
                    }
                    auto effect{action->createEffect()};
                    const auto &final_effect{
                        game().replacementManager().applyReplacementEffects(
                            *effect, game())};
                    // should add to stack and resolve later, but for now just
                    // apply immediately as we only have cards
                    auto event{final_effect.apply(game())};
                    game().eventManager().notify(*event, game());
                }
                catch (const std::exception &e)
                {
                    std::cout << "Invalid input: " << e.what() << '\n';
                }
            }
        }
        return std::move(m_next_phase);
    }
} // namespace dandan::core