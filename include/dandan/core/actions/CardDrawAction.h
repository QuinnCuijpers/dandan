#ifndef DANDAN_CARD_DRAW_ACTION_H
#define DANDAN_CARD_DRAW_ACTION_H

#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
#include <iostream>

namespace dandan::core
{
    class Game;

    class CardDrawAction : public IAction
    {
    public:
        CardDrawAction(Game *game) : m_game{game}
        {
        }

        // TODO: actions should create events, but for now we will just execute
        // the action directly
        void execute() override
        {
            std::cout << "Executing card draw action\n";
            m_game->getActivePlayer().drawCard(m_game->getDeck());
        }

    private:
        [[maybe_unused]] Game *m_game;
    };
} // namespace dandan::core

#endif