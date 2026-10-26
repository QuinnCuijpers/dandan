#include "dandan/core/Hand.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/Game.h"
#include "dandan/core/Zone.h"
#include <algorithm>
#include <iostream>

namespace dandan::core
{
    Hand::Hand(std::vector<CardID> cards) : m_cards{std::move(cards)}
    {
    }

    const std::vector<CardID> &Hand::getCards() const
    {
        return m_cards;
    }

    CardID Hand::getCard(int index) const
    {
        return m_cards[index];
    }

    CardID Hand::getCard(int index)
    {
        auto card{m_cards[index]};
        // erase chosen over pop and swap as we want to maintain card order
        // in hand while in the backend it is more effiecient to pop and
        // swap, the order of cards remaining constant makes UI later easier
        // to implement
        m_cards.erase(m_cards.begin() + index);
        return card;
    }

    void Hand::removeCard(const Card &card)
    {
        auto card_id = card.getID();
        auto iter = std::find_if(m_cards.begin(), m_cards.end(),
                                 [&card_id](const CardID &other)
                                 { return card_id == other; });
        if (iter != m_cards.end())
        {
            std::cout << "Removing card:" << card.getData().name << '\n';
            m_cards.erase(iter);
        }
        else
        {
            std::cout << "Couldn't find card " << card.getData().name
                      << " in hand to remove\n";
        }
    }

    void Hand::addCard(Card &card)
    {
        card.setZone(Zone::HAND);
        m_cards.emplace_back(card.getID());
    }

    void Hand::discardCard(CardID card_id, ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        auto *card = card_registry.get(card_id);
        std::cout << "Discarding card " << card->getData().name << '\n';
        removeCard(*card);
        game.graveyard().addCard(*card);
    }
} // namespace dandan::core
