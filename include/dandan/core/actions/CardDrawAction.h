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
     * @brief An action that represents drawing a card.
     * @class CardDrawAction
     *
     * @implements IAction
     */
    class CardDrawAction : public IAction
    {
    public:
        CardDrawAction() = default;

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game) override;
    };
} // namespace dandan::core

#endif
