#ifndef DANDAN_GRAVEYARD_H
#define DANDAN_GRAVEYARD_H

#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Zone.h"

namespace dandan::core
{
    class Graveyard
    {
    public:
        Graveyard() = default;

        /** Adds a card to the graveyard.
         * @param card The card to add.
         */
        void addCard(Card &card)
        {
            card.setZone(Zone::GRAVEYARD);
            card.resetState();
            m_cards.emplace_back(card.getID());
        }

        [[nodiscard]] const std::vector<CardID> &getCards() const
        {
            return m_cards;
        }

    private:
        std::vector<CardID> m_cards;
    };
} // namespace dandan::core

#endif