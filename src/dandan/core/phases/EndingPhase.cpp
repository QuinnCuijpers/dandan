#include "dandan/core/phases/EndingPhase.h"
#include "dandan/core/Game.h"
#include "dandan/log.h"
#include <string>

// TODO: clear mana pools at end of turn
namespace dandan::core
{

    void EndingPhase::handleNextStep()
    {
        switch (m_step)
        {
        case Step::End:
            std::cout << "Handling end step\n";
            // game().render();
            m_step = Step::Cleanup;
            break;
        case Step::Cleanup:
            //         514.1. First, if the active player’s hand contains more
            //         cards than their maximum hand size (normally
            // seven), they discard enough cards to reduce their hand size to
            // that number. This turn-based action doesn’t use the stack.
            std::cout << "Handling cleanup step\n";
            // game().render();
            // TODO: both players discard down to their maximum hand size, not
            // just active player
            if (game().activePlayer().hand().getCards().size() >
                game().activePlayer().maxHandSize())
            {
                DLOGI << "Active player has more cards than their maximum hand "
                         "size, discarding down to max hand size\n";
                while (game().activePlayer().hand().getCards().size() >
                       game().activePlayer().maxHandSize())
                {
                    std::cout
                        << "You have "
                        << game().activePlayer().hand().getCards().size()
                        << " cards in hand, but your maximum hand size is "
                        << game().activePlayer().maxHandSize()
                        << ". Please choose a card to discard: ";
                    try
                    {
                        std::string input;
                        std::getline(game().istream(), input);
                        int card_id = std::stoi(input);
                        auto *card{game().getCardByID(card_id)};
                        game().activePlayer().discardCard(*card);
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << "Invalid input: " << e.what() << '\n';
                    }
                }
            }
            m_step = Step::Done;
            break;
        case Step::Done:
            assert(false && "Unreachable code in EndingPhase::handleNextStep");
            break;
        }
    }
    [[nodiscard]] std::unique_ptr<IPhase> EndingPhase::handle()
    {
        std::cout << "Handling ending phase\n";
        while (m_step != Step::Done)
        {
            handleNextStep();
        }
        return std::move(m_next_phase);
    }

} // namespace dandan::core