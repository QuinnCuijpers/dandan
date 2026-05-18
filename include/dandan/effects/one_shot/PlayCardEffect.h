#ifndef DANDAN_PLAYCARDEFFECT_H
#define DANDAN_PLAYCARDEFFECT_H

#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
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

        std::unique_ptr<events::IEvent> apply(
            [[maybe_unused]] core::Game &game) const override
        {
            std::cout << "Applying PlayCardEffect\n";
            game.activePlayer().playCard(m_card);
            if (m_card.getData().getType() == core::CardData::Type::Land)
            {
                game.activePlayer().setPlayedLandThisTurn(true);
            }
            return std::make_unique<events::ETBEvent>(m_card.getID(),
                                                      m_card.getControllerID());
        }

    private:
        core::Card &m_card;
    };
} // namespace dandan::effects

#endif