#include "dandan/effects/one_shot/ScryEffect.h"
#include "dandan/core/Game.h"
namespace dandan::effects
{

    std::unique_ptr<events::IEvent> ScryEffect::apply(
        [[maybe_unused]] core::Game &game) const
    {
        auto cards = game.library().draw(m_scry_amount);
        std::cout << "Scryed cards: [ ";
        for (const auto &card : cards)
        {
            auto *cardp{game.getCardByID(card)};
            std::cout << cardp->getData().getName() << " ,";
        }
        std::cout << " ]\n";

        while (!cards.empty())
        {
            // choose a card index if cards.size() > 1, otherwise just put the
            // card on top or bottom
            int card_index{-1};
            if (cards.size() > 1)
            {
                std::cout << "Choose a card index to scry (0 to "
                          << cards.size() - 1 << "): ";
                std::string input;
                std::getline(game.istream(), input);
                card_index = std::stoi(input);
                if (card_index < 0 ||
                    card_index >= static_cast<int>(cards.size()))
                {
                    std::cout << "Invalid card index";
                    continue;
                }
            }
            else
            {
                card_index = 0;
            }

            // ask to put on top or bottom
            std::cout << "Put card on top or bottom? (top/bottom) ";
            std::string input;
            std::getline(game.istream(), input);
            if (input == "top")
            {
                game.library().getCards().push_front(cards[card_index]);
                cards.erase(cards.begin() + card_index);
            }
            else if (input == "bottom")
            {
                game.library().getCards().push_back(cards[card_index]);
                cards.erase(cards.begin() + card_index);
            }
            else
            {
                std::cout << "Invalid input, please enter top or bottom\n";
                continue;
            }
        }
        return nullptr;
    }

} // namespace dandan::effects