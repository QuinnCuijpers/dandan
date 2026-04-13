#ifndef DANDAN_BOARD_H
#define DANDAN_BOARD_H

#include "dandan/core/Deck.h"
#include "dandan/core/Hand.h"
#include <iostream>

namespace dandan::core
{

    class Board
    {
    public:
        Board() : m_deck{}, m_hand{}
        {
            auto new_hand_cards{m_deck.draw(7)};
            m_hand = Hand{new_hand_cards};
            std::cout << "Board initialized with deck and hand.\n";
        };

        void printCards() const;

    private:
        Deck m_deck{};
        Hand m_hand{};
        // Battlefield m_battlefield;
        // Graveyard m_graveyard;
        // Stack m_stack;
        // EventManager m_event_manager;
    };

} // namespace dandan::core

#endif