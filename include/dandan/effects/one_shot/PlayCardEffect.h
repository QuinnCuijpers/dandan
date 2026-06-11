#ifndef DANDAN_PLAYCARDEFFECT_H
#define DANDAN_PLAYCARDEFFECT_H

#include "dandan/abilities/SpellAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/ModalEffect.h"
#include "dandan/events/IEvent.h"
#include <algorithm>
#include <iostream>
#include <memory>

// TODO: add doc explaining how this is different from ETBEffect
namespace dandan::effects
{
    /** @brief Represents the effect of playing a card.
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

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<PlayCardEffect>(m_card);
        }

        std::unique_ptr<events::IEvent> apply_impl(
            [[maybe_unused]] core::Game &game) const override
        {
            std::cout << "Applying PlayCardEffect\n";
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

            auto *cardp = game.getCardByID(m_card.getID());
            if (cardp->getData().getType() == core::CardData::Type::Instant ||
                cardp->getData().getType() == core::CardData::Type::Sorcery)
            {
                auto spell_ability_it{std::find_if(
                    cardp->getData().getAbilities().begin(),
                    cardp->getData().getAbilities().end(),
                    [](const auto &ability)
                    {
                        return dynamic_cast<const abilities::SpellAbility *>(
                                   ability.get()) != nullptr;
                    })};

                if (spell_ability_it == cardp->getData().getAbilities().end())
                {
                    throw std::runtime_error(
                        "Instant or sorcery card does not have a spell "
                        "ability");
                }
                const auto &spell_ability =
                    dynamic_cast<const abilities::SpellAbility *>(
                        spell_ability_it->get());
                for (const auto &effect : spell_ability->effects())
                {
                    if (const auto *modal_effect =
                            dynamic_cast<const ModalEffectDefinition *>(
                                effect.get()))
                    // choose mode
                    {
                        std::cout << modal_effect->display();
                        std::cout << "Choose an option (0-"
                                  << modal_effect->getOptions().size() - 1
                                  << "): ";
                        std::string input;
                        std::getline(game.istream(), input);
                        int choice = std::stoi(input);
                        if (choice < 0 ||
                            choice >= static_cast<int>(
                                          modal_effect->getOptions().size()))
                        {
                            throw std::runtime_error(
                                "Invalid choice for modal effect");
                        }
                        cardp->addModalChoice(*modal_effect, choice);

                        // choose targets
                        // if (effect.requiresTargets())
                        // {
                        // }
                    }
                }
            }

            game.moveCardFromZone(game.getPlayer(m_card.getControllerID()),
                                  m_card);
            m_card.setZone(core::Zone::STACK);
            game.stack().push(m_card.getID());
            return nullptr;
        }

    private:
        core::Card &m_card;
    };
} // namespace dandan::effects

#endif
