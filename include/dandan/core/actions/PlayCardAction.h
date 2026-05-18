#ifndef DANDAN_PLAYCARDACTION_H
#define DANDAN_PLAYCARDACTION_H

#include "dandan/abilities/StaticAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/continuous/replacement/IReplacementEffect.h"
#include "dandan/effects/one_shot/ETBEffect.h"
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

        // TODO: move to a cpp file
        std::unique_ptr<effects::IOneShotEffect> createEffect() override
        {
            // lands dont use the stack and their effects are applied
            // immediately
            const auto &data = m_card.getData();
            if (data.getType() == CardData::Type::Land)
            {
                std::cout << "Playing card: " << data.getName() << '\n';
                m_game.eventManager().subscribe(m_card);

                for (const auto &ability : m_card.getData().getAbilities())
                {
                    if (const auto *static_ability =
                            dynamic_cast<const abilities::StaticAbility *>(
                                ability.get()))
                    {
                        if (static_ability->getType() ==
                            abilities::StaticAbility::Type::Replacement)
                        {
                            const auto *replacement_ability = dynamic_cast<
                                const effects::IReplacementEffect *>(
                                static_ability->getEffect());
                            std::cout << "Subscribing replacement ability to "
                                         "replacement manager\n";
                            m_game.replacementManager().subscribe(
                                replacement_ability);
                        }
                    }
                }
                std::cout << m_game.eventManager().size()
                          << " effects subscribed\n";
                // lands dont use the stack and thus immediately enter
                return std::make_unique<effects::ETBEffect>(m_card);
            }

            // add paying mana cost
            // add moving onto the stack
            if (data.getType() == CardData::Type::Creature)
            {
                std::cout << "Playing card: " << data.getName() << '\n';
                return std::make_unique<effects::PlayCardEffect>(m_card);
            }

            throw std::runtime_error(
                "Only land/creature cards can be played for now");
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