#ifndef DANDAN_PLAYCARDEFFECT_H
#define DANDAN_PLAYCARDEFFECT_H

#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/events/ETBEvent.h"
#include "dandan/events/IEvent.h"
#include <iostream>
#include <memory>

namespace dandan::effects
{
    class PlayCardEffect : public IOneShotEffect
    {
    public:
        explicit PlayCardEffect(core::Card &card) : m_card{card}
        {
        }

        // TODO: fix double move of card
        // should be fine after flyweight pattern is implemented and cards are
        // just static references to card data and copyable data structures
        // instead of unique pointers
        std::unique_ptr<events::IEvent> apply(
            [[maybe_unused]] core::Game &game) override
        {
            std::cout << "Applying PlayCardEffect\n";
            game.activePlayer().playCard(m_card);
            return std::make_unique<events::ETBEvent>(m_card);
        }

    private:
        core::Card &m_card;
    };
} // namespace dandan::effects

#endif