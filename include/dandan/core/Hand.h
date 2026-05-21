#ifndef DANDAN_HAND_H
#define DANDAN_HAND_H

#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include <algorithm>
#include <vector>

namespace dandan::core
{
    class Hand
    {
    public:
        Hand() = default;

        explicit Hand(std::vector<CardID> cards) : m_cards{std::move(cards)}
        {
        }

        [[nodiscard]] const std::vector<CardID> &getCards() const
        {
            return m_cards;
        }

        [[nodiscard]] CardID getCard(int index) const
        {
            return m_cards[index];
        }

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

        void addCard(Card &card)
        {
            card.setZone(Zone::HAND);
            m_cards.emplace_back(card.getID());
        }

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

        void insertAt(int index, Card &card)
        {
            card.setZone(Zone::HAND);
            m_cards.insert(m_cards.begin() + index, card.getID());
        }

        void discardCard(Card &card)
        {
            std::cout << "Discarding card " << card.getData().getName() << '\n';
            // TODO: move to graveyard instead of just removing from hand
            // awaiting implementation of graveyard
            // and gamewise src -> dest moving of cards
            card.setZone(Zone::GRAVEYARD);
            auto card_id = card.getID();
            m_cards.erase(std::find(m_cards.begin(), m_cards.end(), card_id));
        }

    private:
        std::vector<CardID> m_cards;
    };
} // namespace dandan::core

#endif