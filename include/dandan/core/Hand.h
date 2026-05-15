#ifndef DANDAN_HAND_H
#define DANDAN_HAND_H

#include "dandan/core/Card.h"
#include "dandan/log.h"
#include <algorithm>
#include <vector>

namespace dandan::core
{
    class Hand
    {
    public:
        Hand() = default;
        explicit Hand(std::vector<Card> cards) : m_cards(std::move(cards))
        {
        }

        [[nodiscard]] const std::vector<Card> &getCards() const
        {
            return m_cards;
        }

        [[nodiscard]] Card getCard(int index)
        {
            auto card{m_cards[index]};
            // erase chosen over pop and swap as we want to maintain card order
            // in hand while in the backend it is more effiecient to pop and
            // swap, the order of cards remaining constant makes UI later easier
            // to implement
            m_cards.erase(m_cards.begin() + index);
            return card;
        }

        void addCard(Card card)
        {
            m_cards.emplace_back(card);
        }

        void addCards(std::vector<Card> cards)
        {
            std::transform(std::make_move_iterator(cards.begin()),
                           std::make_move_iterator(cards.end()),
                           std::back_inserter(m_cards),
                           [](Card card) { return card; });
        }

        void insertAt(int index, Card card)
        {
            m_cards.insert(m_cards.begin() + index, card);
        }

        void discardCard(int index)
        {
            DLOGI << "Discarding card " << m_cards[index] << " at index "
                  << index << '\n';
            // TODO: move to graveyard instead of just removing from hand
            // awaiting implementation of graveyard
            // and gamewise src -> dest moving of cards
            m_cards.erase(m_cards.begin() + index);
        }

    private:
        std::vector<Card> m_cards;
    };
} // namespace dandan::core

#endif