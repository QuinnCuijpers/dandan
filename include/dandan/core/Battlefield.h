#ifndef DANDAN_BOARD_H
#define DANDAN_BOARD_H

#include "dandan/core/Card.h"
#include <memory>
#include <utility>
#include <vector>
namespace dandan::core
{

    using Permanent = std::unique_ptr<Card>;

    class Battlefield
    {
    public:
        void addCard(std::unique_ptr<Card> card)
        {
            m_permanents.emplace_back(std::move(card));
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