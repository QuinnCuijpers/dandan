#ifndef DANDAN_LIBRARY_H
#define DANDAN_LIBRARY_H

#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include <algorithm>
#include <deque>
#include <filesystem>
#include <vector>

namespace dandan::core
{

    class Library
    {

    public:
        Library() = default;

        explicit Library(std::vector<Card> &cards)
        {
            std::transform(cards.begin(), cards.end(),
                           std::back_inserter(m_cards),
                           [](const Card &card) { return card.getID(); });
        }

        void addCard(Card &card)
        {
            card.setZone(Zone::LIBRARY);
            m_cards.emplace_back(card.getID());
        }

        [[nodiscard]] std::deque<CardID> &getCards()
        {
            return m_cards;
        }

        [[nodiscard]] const std::deque<CardID> &getCards() const
        {
            return m_cards;
        }

        CardID draw();
        std::vector<CardID> draw(int count);

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