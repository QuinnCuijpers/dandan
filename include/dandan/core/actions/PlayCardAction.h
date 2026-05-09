#ifndef DANDAN_PLAYCARDACTION_H
#define DANDAN_PLAYCARDACTION_H

#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/PlayCardEffect.h"
#include <memory>

namespace dandan::core
{
    class PlayCardAction : public IAction
    {
    public:
        PlayCardAction(Card &card, Game &game) : m_card{card}, m_game{game}
        {
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect() override
        {
            // lands dont use the stack and their effects are applied
            // immediately
            const auto &data = m_card.getData();
            if (data.getType() == CardData::Land)
            {
                std::cout << "Playing card: " << data.getName() << '\n';
                for (const auto &ability : data.getAbilities())
                {
                    m_game.eventManager().subscribe(ability.get());
                }

                // for (const auto &ability : m_card->getAbilities())
                // {
                //     // if (ability->getType() ==
                //     //     abilities::StaticAbility::Replacement)
                //     // {
                //     //
                //     m_game.getReplacementManager().subscribe(ability.get());
                //     // }
                // }

                std::cout << m_game.eventManager().size()
                          << " effects subscribed\n";
                return std::make_unique<effects::PlayCardEffect>(m_card);
            }
            throw std::runtime_error("Only land cards can be played for now");
        }

    private:
        // TODO: consider not having this take a game as member variable and
        // just pass it in as a parameter to createEffect, as the action itself
        // doesn't need to know about the game, only the effect does when it
        // gets applied.
        Card m_card;
        Game &m_game;
    };
} // namespace dandan::core

#endif // DANDAN_PLAYCARDACTION_H