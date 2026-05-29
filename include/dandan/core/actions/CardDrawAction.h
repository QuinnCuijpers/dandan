#ifndef DANDAN_CARD_DRAW_ACTION_H
#define DANDAN_CARD_DRAW_ACTION_H

#include "dandan/core/Game.h"
#include "dandan/core/PlayerID.h"
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
        /** Constructor
         * @param player The player who will draw the card.
         */
        explicit CardDrawAction(PlayerID player) : m_player{player}
        {
        }

        [[nodiscard]] ActionActor getActor() const override
        {
            return m_player;
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game) override;

    private:
        PlayerID m_player;
    };
} // namespace dandan::core

#endif
