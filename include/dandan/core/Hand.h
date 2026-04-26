#ifndef DANDAN_HAND_H
#define DANDAN_HAND_H

#include "dandan/core/Card.h"
#include <algorithm>
#include <memory>
#include <vector>

namespace dandan::core
{
    class Hand
    {
    public:
        Hand() = default;
        explicit Hand(std::vector<std::unique_ptr<Card>> cards)
            : m_cards(std::move(cards))
        {
        }

        [[nodiscard]] const std::vector<std::unique_ptr<Card>> &getCards() const
        {
            return m_cards;
        }

        [[nodiscard]] std::unique_ptr<Card> getCard(int index)
        {
            auto card{std::move(m_cards[index])};
            // erase chosen over pop and swap as we want to maintain card order
            // in hand while in the backend it is more effiecient to pop and
            // swap, the order of cards remaining constant makes UI later easier
            // to implement
            m_cards.erase(m_cards.begin() + index);
            return card;
        }

        void addCards(std::vector<std::unique_ptr<Card>> cards)
        {
            std::transform(std::make_move_iterator(cards.begin()),
                           std::make_move_iterator(cards.end()),
                           std::back_inserter(m_cards),
                           [](std::unique_ptr<Card> &&card)
                           { return std::move(card); });
        }

    private:
        std::vector<std::unique_ptr<Card>> m_cards;
    };
} // namespace dandan::core

#endif