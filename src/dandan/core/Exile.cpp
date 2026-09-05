#include "dandan/core/Exile.h"
#include "dandan/core/Card.h"
#include "dandan/core/Zone.h"
#include <algorithm>

namespace dandan::core
{
    void Exile::addCard(Card &card)
    {
        card.setZone(Zone::EXILE);
        m_cards.emplace_back(card.getID());
    }
    void Exile::removeCard(const Card &card)
    {
        auto iter = std::find(m_cards.begin(), m_cards.end(), card.getID());
        if (iter != m_cards.end())
        {
            m_cards.erase(iter);
        }
    }
} // namespace dandan::core
