#ifndef DANDAN_GRAVEYARDCOUNT_H
#define DANDAN_GRAVEYARDCOUNT_H

#include "dandan/numbers/INumber.h"
#include <algorithm>

namespace dandan::numbers
{
    class GraveyardCount : public INumber
    {
    public:
        explicit GraveyardCount(std::string name) : m_name(std::move(name))
        {
        }

        [[nodiscard]] std::string getName() const
        {
            return m_name;
        }

        [[nodiscard]] int getValue(
            [[maybe_unused]] core::Game &game) const override
        {
            auto count{std::count_if(game.graveyard().getCards().begin(),
                                     game.graveyard().getCards().end(),
                                     [this, &game](const auto &card_id)
                                     {
                                         auto card{game.getCardByID(card_id)};
                                         return card->getData().getName() ==
                                                m_name;
                                     })};
            return static_cast<int>(count);
        }

        [[nodiscard]] std::unique_ptr<INumber> clone() const override
        {
            return std::make_unique<GraveyardCount>(m_name);
        }

    private:
        std::string m_name;
    };
} // namespace dandan::numbers

#endif // DANDAN_GRAVEYARDCOUNT_H