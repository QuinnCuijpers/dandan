#ifndef DANDAN_EXILE_H
#define DANDAN_EXILE_H

#include "dandan/core/Card.h"
#include <vector>

namespace dandan::core
{
    class Exile
    {
    public:
        Exile() = default;

        /** Adds a card to the exile.
         * @param card The card to add.
         */
        void addCard(Card &card)
        {
            card.setZone(Zone::EXILE);
            m_cards.emplace_back(card.getID());
        }

        /** Gets the list of cards in the exile.
         * @return A constant reference to the vector of card IDs.
         */
        [[nodiscard]] const std::vector<CardID> &getCards() const
        {
            return m_cards;
        }

    private:
        std::vector<CardID> m_cards;
    };
} // namespace dandan::core

#endif