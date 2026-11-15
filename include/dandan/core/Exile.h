#ifndef DANDAN_EXILE_H
#define DANDAN_EXILE_H

#include "dandan/core/CardID.h"
#include <vector>

namespace dandan::core
{
    class Card;

    /** @brief The zone for exiled cards.
     * @class Exile
     */
    class Exile
    {
    public:
        /** Constructs an empty exile zone. */
        Exile() = default;

        /** Adds a card to the exile.
         * @param card The card to add.
         */
        void addCard(Card &card);

        /** Removes a card from the exile.
         * @param card The card to remove.
         */
        void removeCard(const Card &card);

        /** Gets the list of cards in the exile.
         * @return A constant reference to the vector of card IDs.
         */
        [[nodiscard]] const std::vector<CardID> &getCards() const;

    private:
        std::vector<CardID> m_cards;
    };
} // namespace dandan::core

#endif
