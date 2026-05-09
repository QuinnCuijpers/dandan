#ifndef DANDAN_BOARD_H
#define DANDAN_BOARD_H

#include "Card.h"
#include <vector>

namespace dandan::core
{

    using Permanent = Card;

    class Battlefield
    {
    public:
        void addCard(Card card)
        {
            m_permanents.emplace_back(card);
        }

        [[nodiscard]] Permanent getPermanent(int card_index)
        {
            auto card{m_permanents[card_index]};
            // erase chosen over pop and swap as we want to maintain card order
            // in hand while in the backend it is more effiecient to pop and
            // swap, the order of cards remaining constant makes UI later easier
            // to implement
            m_permanents.erase(m_permanents.begin() + card_index);
            return card;
        }

        [[nodiscard]] const std::vector<Permanent> &getPermanents() const
        {
            return m_permanents;
        }

    private:
        std::vector<Permanent> m_permanents;
    };

} // namespace dandan::core

#endif