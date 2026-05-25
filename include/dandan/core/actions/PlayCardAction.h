#ifndef DANDAN_PLAYCARDACTION_H
#define DANDAN_PLAYCARDACTION_H

#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>

namespace dandan::core
{
    /**
     * @brief An action that represents playing a card.
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
         */
        explicit PlayCardAction(CardID card_id) : m_card_id{card_id}
        {
        }

        /** Get the card ID of the card to play.
         * @return The card ID of the card to play.
         */
        [[nodiscard]] CardID getCardID() const
        {
            return m_card_id;
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game) override;

    private:
        CardID m_card_id;
    };
} // namespace dandan::core

#endif // DANDAN_PLAYCARDACTION_H
