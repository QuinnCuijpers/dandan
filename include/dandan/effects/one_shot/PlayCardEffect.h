#ifndef DANDAN_PLAYCARDEFFECT_H
#define DANDAN_PLAYCARDEFFECT_H

#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/events/ETBEvent.h"
#include "dandan/events/IEvent.h"
#include <iostream>
#include <memory>

// TODO: add doc explaining how this is different from ETBEffect
namespace dandan::effects
{
    /** Represents the effect of playing a card.
     * @class PlayCardEffect
     *
     * @implements IOneShotEffect
     */
    class PlayCardEffect : public IOneShotEffect
    {
    public:
        /** Constructor
         *@param card The card that would be played
         */
        explicit PlayCardEffect(core::Card &card) : m_card{card}
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<PlayCardEffect>(m_card);
        }

        std::unique_ptr<events::IEvent> apply(
            [[maybe_unused]] core::Game &game) const override
        {
            std::cout << "Applying PlayCardEffect\n";
            // TODO: move to stack instead of playing the card
            const auto *mana_cost = m_card.getData().getCost();
            if (game.activePlayer().manaPool().canPay(*mana_cost))
            {
                game.activePlayer().manaPool().pay(*mana_cost);
            }
            else
            {
                throw std::runtime_error(
                    "Not enough mana to play card " +
                    std::string{m_card.getData().getName()});
            }
            game.activePlayer().playCard(m_card);
            return std::make_unique<events::ETBEvent>(m_card.getID(),
                                                      m_card.getControllerID());
        }

    private:
        core::Card &m_card;
    };
} // namespace dandan::effects

#endif