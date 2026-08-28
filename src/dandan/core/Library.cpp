#include "dandan/core/Library.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include <iostream>
#include <vector>

namespace dandan::core
{

    CardID Library::draw()
    {
        if (m_cards.empty())
        {
            std::cout << "library is empty, cannot draw card\n";
            return CardID::getInvalidID();
        }
        CardID drawn_card = m_cards.front();
        m_cards.pop_front();
        return drawn_card;
    }

    std::vector<CardID> Library::draw(int count)
    {
        std::vector<CardID> drawn_cards;
        for (int i = 0; i < count && !m_cards.empty(); ++i)
        {
            drawn_cards.push_back(m_cards.front());
            m_cards.pop_front();
        }
        return drawn_cards;
    }

    std::vector<CardID> Library::mill(core::ExecutionContext exec_ctx,
                                      int count)
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        auto res{std::vector<CardID>{}};
        for (int i = 0; i < count && !m_cards.empty(); ++i)
        {
            CardID milled_card = m_cards.front();
            res.push_back(milled_card);
            m_cards.pop_front();
            game.graveyard().addCard(*card_registry[milled_card]);
        }
        return res;
    }
} // namespace dandan::core
