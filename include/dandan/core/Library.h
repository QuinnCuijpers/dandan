#ifndef DANDAN_LIBRARY_H
#define DANDAN_LIBRARY_H

#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include <algorithm>
#include <deque>
#include <filesystem>
#include <random>
#include <vector>

namespace dandan::core
{

    /** @brief A class that represents the library of the game.
     * @class Library
     */
    class Library
    {

    public:
        Library() = default;

        /** Constructs a library with the given cards.
         * @param cards The cards vector to initialize the library with.
         */
        explicit Library(std::vector<Card> &cards)
        {
            std::transform(cards.begin(), cards.end(),
                           std::back_inserter(m_cards),
                           [](const Card &card) { return card.getID(); });
            std::shuffle(m_cards.begin(), m_cards.end(),
                         std::mt19937{std::random_device{}()});
        }

        /** Adds a card to the library.
         * @param card The card to add.
         */
        void addCard(Card &card)
        {
            card.setZone(Zone::LIBRARY);
            m_cards.emplace_back(card.getID());
        }

        /** Gets the cards in the library mutably.
         * @return A reference to the deque of card IDs in the library.
         */
        [[nodiscard]] std::deque<CardID> &getCards()
        {
            return m_cards;
        }

        /** Gets the cards in the library immutably.
         * @return A const reference to the deque of card IDs in the library.
         */
        [[nodiscard]] const std::deque<CardID> &getCards() const
        {
            return m_cards;
        }

        /** Shuffles the cards in the library.
         */
        void shuffle()
        {
            std::shuffle(m_cards.begin(), m_cards.end(),
                         std::mt19937{std::random_device{}()});
        }

        /** Draws a card from the library.
         * @return The card ID of the drawn card.
         */
        CardID draw();

        /** Draws multiple cards from the library.
         * @param count The number of cards to draw.
         * @return A vector of the drawn card IDs.
         */
        std::vector<CardID> draw(int count);

        /** Peeks at the top cards in the library.
         * @param count The number of cards to peek at.
         * @return A vector of the peeked card IDs.
         */
        [[nodiscard]] std::vector<CardID> peek(int count) const;

    private:
        std::filesystem::path m_decklist_path{DANDAN_DECKLIST};
        std::deque<CardID> m_cards;
#ifdef DANDAN_SERIALIZE
        void loadCards(const std::filesystem::path &path);
#endif
    };
} // namespace dandan::core
#endif
