#ifndef DANDAN_PLAYCARDACTION_H
#define DANDAN_PLAYCARDACTION_H

#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>

namespace dandan::core
{
    /**
     * An action that represents playing a card.
     * @class PlayCardAction
     *
     * @implements IAction
     */
    class PlayCardAction : public IAction
    {
    public:
        /**
         * Constructs a new play card action.
         * @param card_id The card_id of the card to play.
         * @param game The game instance.
         */
        PlayCardAction(CardID card_id, Game &game)
            : m_card_id{card_id}, m_game{game}
        {
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game) override;

    private:
        // TODO: consider not having this take a game as member variable and
        // just pass it in as a parameter to createEffect, as the action itself
        // doesn't need to know about the game, only the effect does when it
        // gets applied.
        CardID m_card_id;
        Game &m_game;
    };
} // namespace dandan::core

#endif // DANDAN_PLAYCARDACTION_H