#ifndef DANDAN_HAND_H
#define DANDAN_HAND_H

#include <string>
#include <vector>

namespace dandan::core
{
    class Hand
    {
    public:
        Hand() = default;
        explicit Hand(std::vector<std::string> cards)
            : m_cards(std::move(cards))
        {
        }

        const std::vector<std::string> &getCards() const
        {
            return m_cards;
        }

    private:
        std::vector<std::string> m_cards;
    };
} // namespace dandan::core

#endif