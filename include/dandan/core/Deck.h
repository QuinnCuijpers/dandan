#ifndef DECK_H
#define DECK_H

#include "dandan/core/Card.h"
#include <algorithm>
#include <deque>
#include <filesystem>
#include <vector>

const static auto DANDAN_DECKLIST =
    std::filesystem::path(DANDAN_PROJECT_SOURCE) / "data/temp_decklist.txt";

namespace dandan::core
{

    class Deck
    {

    public:
        // TODO: if DANDAN_build-serialize is not defined then the deck will be
        // empty. for testing purposes, we should have a defaultly defined deck
#ifdef DANDAN_BUILD_SERIALIZE
        Deck();
        explicit Deck(std::filesystem::path path);
#else
        Deck() = default;
#endif
        explicit Deck(std::vector<Card> &cards)
        {
            std::transform(cards.begin(), cards.end(),
                           std::back_inserter(m_cards),
                           [](const Card &card) { return card; });
        }

        [[nodiscard]] std::deque<Card> &getCards()
        {
            return m_cards;
        }

        [[nodiscard]] const std::deque<Card> &getCards() const
        {
            return m_cards;
        }

        std::vector<Card> draw(int count = 1);

        void peek(int count) const;

    private:
        std::filesystem::path m_decklist_path{DANDAN_DECKLIST};
        std::deque<Card> m_cards;
#ifdef DANDAN_BUILD_SERIALIZE
        void loadCards(const std::filesystem::path &path);
#endif
    };
} // namespace dandan::core
#endif