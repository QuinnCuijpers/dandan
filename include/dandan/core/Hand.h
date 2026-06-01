#ifndef DANDAN_HAND_H
#define DANDAN_HAND_H

#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include <algorithm>
#include <stdexcept>
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
        explicit Hand(std::vector<CardID> cards) : m_cards{std::move(cards)}
        {
        }

        /** Gets the cards in the hand immutably.
         * @return A const reference to the vector of card IDs in the hand.
         */
        [[nodiscard]] const std::vector<CardID> &getCards() const
        {
            return m_cards;
        }

        /** Gets a card from the hand at the specified index.
         * @param index The index of the card to get.
         * @return The card ID at the specified index.
         */
        [[nodiscard]] CardID getCard(int index) const
        {
            return m_cards[index];
        }

        /** Gets a card from the hand at the specified index and removes it from
         * the hand.
         * @param index The index of the card to get.
         * @return The card ID at the specified index.
         */
        [[nodiscard]] CardID getCard(int index)
        {
            auto card{m_cards[index]};
            // erase chosen over pop and swap as we want to maintain card order
            // in hand while in the backend it is more effiecient to pop and
            // swap, the order of cards remaining constant makes UI later easier
            // to implement
            m_cards.erase(m_cards.begin() + index);
            return card;
        }

        /** Removes a card from the hand.
         * @param card The card to remove.
         */
        void removeCard(const Card &card)
        {
            auto card_id = card.getID();
            auto iter = std::find_if(m_cards.begin(), m_cards.end(),
                                     [&card_id](const CardID &other)
                                     { return card_id == other; });
            if (iter != m_cards.end())
            {
                m_cards.erase(iter);
            }
        }

        /** Adds a card to the hand.
         * @param card The card to add.
         */
        void addCard(Card &card)
        {
            card.setZone(Zone::HAND);
            m_cards.emplace_back(card.getID());
        }

        /** Adds multiple cards to the hand.
         * @param cards The vector of cards to add.
         */
        void addCards(std::vector<Card> &cards)
        {
            auto cardToHand = [](Card &card)
            {
                card.setZone(Zone::HAND);
                return card.getID();
            };
            std::transform(cards.begin(), cards.end(),
                           std::back_inserter(m_cards), cardToHand);
        }

        /** Discards a card from the hand.
         * @param card The card to discard.
         */
        void discardCard(Card &card)
        {
            std::cout << "Discarding card " << card.getData().getName() << '\n';
            // TODO: move to graveyard instead of just removing from hand
            // awaiting implementation of graveyard
            // and gamewise src -> dest moving of cards
            card.setZone(Zone::GRAVEYARD);
            auto card_id = card.getID();
            auto iter = std::find(m_cards.begin(), m_cards.end(), card_id);
            if (iter == m_cards.end())
            {
                throw std::runtime_error(
                    "Card is not in hand and cannot be discarded");
            }
            m_cards.erase(iter);
        }

    private:
        std::vector<CardID> m_cards;
    };
} // namespace dandan::core

#endif
