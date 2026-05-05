#ifndef DANDAN_CARD_DRAW_ACTION_H
#define DANDAN_CARD_DRAW_ACTION_H

#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::core
{
    class Game;

    class CardDrawAction : public IAction
    {
    public:
        explicit CardDrawAction(Game *game) : m_game{game}
        {
        }

        // TODO: actions should create effects, but for now we will just execute
        // the action directly
        std::unique_ptr<effects::IOneShotEffect> execute() override
        {
            std::cout << "Executing card draw action\n";
            m_game->getActivePlayer().drawCard(m_game->getDeck());
            return std::make_unique<effects::DrawEffect>();
        }

    private:
        [[maybe_unused]] Game *m_game;
    };
} // namespace dandan::core

#endif