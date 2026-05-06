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
        PlayCardEffect(std::unique_ptr<core::Card> &&card)
            : m_card{std::move(card)}
        {
        }

        std::unique_ptr<events::IEvent> apply(
            [[maybe_unused]] core::Game &game) override
        {
            std::cout << "Applying PlayCardEffect\n";
            game.getActivePlayer().playCard(std::move(m_card));
            return std::make_unique<events::ETBEvent>(std::move(m_card));
        }

    private:
        std::unique_ptr<core::Card> m_card;
    };
} // namespace dandan::effects

#endif