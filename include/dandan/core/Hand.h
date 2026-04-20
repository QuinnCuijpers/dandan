#ifndef DANDAN_HAND_H
#define DANDAN_HAND_H

#include "dandan/core/Card.h"
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

    private:
        std::vector<std::unique_ptr<Card>> m_cards;
    };
} // namespace dandan::core

#endif