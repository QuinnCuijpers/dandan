#include "dandan/core/Board.h"

namespace dandan::core
{

    void Board::printCards() const
    {
        std::cout << '\n';
        std::cout << "Cards in deck:\n";
        for (const auto &card : m_deck.getCards())
        {
            std::cout << *card << '\n';
        }
        std::cout << '\n';

        std::cout << "Cards in hand:\n";
        for (const auto &card : m_hand.getCards())
        {
            std::cout << *card << '\n';
        }
    }

} // namespace dandan::core