#include "dandan/core/Graveyard.h"
#include "dandan/core/Zone.h"
#include <algorithm>
#include <iostream>

namespace dandan::core
{
    void Graveyard::addCard(Card &card)
    {
        std::cout << "Adding card " << card.getData().name
                  << " with ID: " << card.getID().getID() << " to graveyard\n";
        card.setZone(Zone::GRAVEYARD);
        card.resetState();
        m_cards.emplace_back(card.getID());
    }

    void Graveyard::removeCard(const Card &card)
    {
        auto iter = std::find(m_cards.begin(), m_cards.end(), card.getID());
        if (iter != m_cards.end())
        {
            m_cards.erase(iter);
        }
    }

    const std::vector<CardID> &Graveyard::getCards() const
    {
        return m_cards;
    }
} // namespace dandan::core
