#include "dandan/core/Library.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include <iostream>
#include <vector>

namespace dandan::core
{

    CardID Library::draw()
    {
        if (m_cards.empty())
        {
            std::cout << "library is empty, cannot draw card\n";
            return CardID::getInvalidID();
        }
        CardID drawn_card = m_cards.front();
        m_cards.pop_front();
        return drawn_card;
    }

    std::vector<CardID> Library::draw(int count)
    {
        std::vector<CardID> drawn_cards;
        for (int i = 0; i < count && !m_cards.empty(); ++i)
        {
            drawn_cards.push_back(m_cards.front());
            m_cards.pop_front();
        }
        return drawn_cards;
    }

    std::vector<CardID> Library::peek(int count) const
    {
        std::vector<CardID> peeked_cards;
        for (int i{}; i < count && i < static_cast<int>(m_cards.size()); ++i)
        {
            const CardID &card_id = m_cards[i];
            peeked_cards.push_back(card_id);
        }
        return peeked_cards;
    }

    void Library::mill(core::Game &game, int count)
    {
        for (int i = 0; i < count && !m_cards.empty(); ++i)
        {
            CardID milled_card = m_cards.front();
            m_cards.pop_front();
            game.graveyard().addCard(*game.getCardByID(milled_card));
        }
    }
} // namespace dandan::core