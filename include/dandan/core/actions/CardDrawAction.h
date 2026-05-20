#ifndef DANDAN_CARD_DRAW_ACTION_H
#define DANDAN_CARD_DRAW_ACTION_H

#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>

namespace dandan::core
{
    class Game;

    /**
     * An action that represents drawing a card.
     * @class CardDrawAction
     *
     * @implements IAction
     */
    class CardDrawAction : public IAction
    {
    public:
        /**
         * Constructs a new card draw action.
         * @param game The game instance.
         */
        explicit CardDrawAction(Game &game) : m_game{game}
        {
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect() override;

    private:
        [[maybe_unused]] Game &m_game;
    };
} // namespace dandan::core

#endif