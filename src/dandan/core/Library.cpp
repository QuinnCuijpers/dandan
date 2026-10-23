#include "dandan/core/Library.h"
#include "dandan/core/CardID.h"
#include "dandan/core/GameState.h"
#include <iostream>
#include <random>
#include <vector>

namespace dandan::core
{
    Library::Library(std::vector<Card> &cards)
    {
        std::transform(cards.begin(), cards.end(), std::back_inserter(m_cards),
                       [](const Card &card) { return card.getID(); });
        std::shuffle(m_cards.begin(), m_cards.end(),
                     std::mt19937{std::random_device{}()});
    }

    void Library::addCardBottom(Card &card)
    {
        card.setZone(Zone::LIBRARY);
        m_cards.emplace_back(card.getID());
    }

    void Library::addCardTop(Card &card)
    {
        card.setZone(Zone::LIBRARY);
        m_cards.emplace_front(card.getID());
    }

    void Library::removeCard(const Card &card)
    {
        auto iter = std::find(m_cards.begin(), m_cards.end(), card.getID());
        if (iter != m_cards.end())
        {
            m_cards.erase(iter);
        }
    }

    [[nodiscard]] std::deque<CardID> &Library::getCards()
    {
        return m_cards;
    }

    [[nodiscard]] const std::deque<CardID> &Library::getCards() const

    {
        return m_cards;
    }

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
        const auto &card_registry{exec_ctx.cards.get()};

        auto res{std::vector<CardID>{}};
        for (int i = 0; i < count && !m_cards.empty(); ++i)
        {
            CardID milled_card = m_cards.front();
            res.push_back(milled_card);
            m_cards.pop_front();
            game.graveyard().addCard(*card_registry.get(milled_card));
        }
        return res;
    }

    void Library::shuffle()
    {
        std::shuffle(m_cards.begin(), m_cards.end(),
                     std::mt19937{std::random_device{}()});
    }
} // namespace dandan::core
