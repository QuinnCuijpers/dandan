#ifndef DANDAN_GRAVEYARD_H
#define DANDAN_GRAVEYARD_H

#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Zone.h"

namespace dandan::core
{
    /**
     * @brief A class representing the graveyard.
     *
     * @class Graveyard
     * The graveyard is a zone where cards go when they are destroyed or
     * discarded.
     */
    class Graveyard
    {
    public:
        Graveyard() = default;

        /** Adds a card to the graveyard.
         * @param card The card to add.
         */
        void addCard(Card &card)
        {
            std::cout << "Adding card " << card.getData().getName()
                      << " with ID: " << card.getID().getID()
                      << " to graveyard\n";
            card.setZone(Zone::GRAVEYARD);
            card.resetState();
            m_cards.emplace_back(card.getID());
        }

        void removeCard(const Card &card)
        {
            auto iter = std::find(m_cards.begin(), m_cards.end(), card.getID());
            if (iter != m_cards.end())
            {
                m_cards.erase(iter);
            }
        }

        /** Gets the cards in the graveyard.
         * @return A const reference to the vector of card IDs.
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