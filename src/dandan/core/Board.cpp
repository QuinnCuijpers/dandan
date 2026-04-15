#include "dandan/core/Board.h"

namespace dandan::core
{

    void Board::printCards() const
    {
        std::cout << '\n';
        std::cout << "Cards in deck:\n";
        auto cards{m_deck.getCards()};
        for (const auto &card : cards)
        {
            std::cout << card << '\n';
        }
        std::cout << '\n';

        std::cout << "Cards in hand:\n";
        auto hand_cards{m_hand.getCards()};
        for (const auto &card : hand_cards)
        {
            std::cout << card << '\n';
        }
    }

} // namespace dandan::core