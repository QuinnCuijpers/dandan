#include "dandan/core/Exile.h"
#include "dandan/core/Card.h"
#include "dandan/core/Zone.h"

namespace dandan::core
{
    void Exile::addCard(Card &card)
    {
        card.setZone(Zone::EXILE);
        m_cards.emplace_back(card.getID());
    }
} // namespace dandan::core
