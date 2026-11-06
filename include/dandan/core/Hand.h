#ifndef DANDAN_HAND_H
#define DANDAN_HAND_H

#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
#include "dandan/core/CardID.h"
#include <algorithm>
#include <vector>

namespace dandan::core
{
    /** @brief A class that represents the hand of the game.
     * @class Hand
     */
    class Hand
    {
    public:
        Hand() = default;

        /** Constructs a hand with the given cards.
         * @param cards The cards vector to initialize the hand with.
         */
        explicit Hand(std::vector<CardID> cards);

        /** Gets the cards in the hand immutably.
         * @return A const reference to the vector of card IDs in the hand.
         */
        [[nodiscard]] const std::vector<CardID> &getCards() const;

        /** Gets a card from the hand at the specified index.
         * @param index The index of the card to get.
         * @return The card ID at the specified index.
         */
        [[nodiscard]] CardID getCard(int index) const;

        /** Gets a card from the hand at the specified index and removes it from
         * the hand.
         * @param index The index of the card to get.
         * @return The card ID at the specified index.
         */
        [[nodiscard]] CardID getCard(int index);

        /** Removes a card from the hand.
         * @param card The card to remove.
         */
        void removeCard(const Card &card);

        /** Adds a card to the hand.
         * @param card The card to add.
         */
        void addCard(Card &card);

        /** Discards a card from the hand.
         * @param card_id The ID of the card to discard.
         * @param game The game instance.
         */
        void discardCard(CardID card_id, ExecutionContext exec_ctx);

    private:
        std::vector<CardID> m_cards;
    };
} // namespace dandan::core

#endif
