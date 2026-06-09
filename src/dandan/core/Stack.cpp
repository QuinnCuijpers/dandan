#include "dandan/core/Stack.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/SpellAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/overloadVisitor.h"
#include <memory>

namespace dandan::core
{
    void Stack::resolveNext(core::Game &game)
    {
        if (m_stack.empty())
        {
            return;
        }

        auto &object{m_stack.back()};

        std::cout << "Resolving object on stack\n";

        bool resolvingSpell{false};

        auto effect{std::visit(
            overloaded{
                [&game, &resolvingSpell](
                    CardID card_id) -> std::unique_ptr<effects::IOneShotEffect>
                {
                    auto *card{game.getCardByID(card_id)};
                    if (card->getData().getType() == CardData::Type::Instant ||
                        card->getData().getType() == CardData::Type::Sorcery)
                    {
                        resolvingSpell = true;

                        auto spell_ability_it{std::find_if(
                            card->getData().getAbilities().begin(),
                            card->getData().getAbilities().end(),
                            [](const auto &ability)
                            {
                                return dynamic_cast<
                                           const abilities::SpellAbility *>(
                                           ability.get()) != nullptr;
                            })};

                        const auto *spell_ability =
                            dynamic_cast<const abilities::SpellAbility *>(
                                spell_ability_it->get());

                        abilities::AbilityContext context{
                            card->getID(), card->getControllerID()};

                        auto effect{spell_ability->createEffect(game, context)};
                        return effect;
                    }
                    return std::make_unique<effects::ETBEffect>(
                        *game.getCardByID(card->getID()));
                },
                [&game, this](const abilities::BoundAbility &ability)
                    -> std::unique_ptr<effects::IOneShotEffect>
                {
                    m_stack.pop_back();
                    return ability.createEffect(game);
                }},
            object)};

        if (effect)
        {
            auto final_effect{game.replacementManager().applyReplacementEffects(
                *effect, game)};
            auto event{final_effect->apply(game)};
            if (event)
            {
                std::cout << "Notifying event\n";
                game.eventManager().notify(*event, game);
            }
        }

        // move card to graveyard if it was a spell
        if (resolvingSpell)
        {
            std::visit(overloaded{[&game](CardID card_id)
                                  {
                                      auto *card{game.getCardByID(card_id)};
                                      game.moveCardFromZone(game.activePlayer(),
                                                            *card);
                                      game.graveyard().addCard(*card);
                                  },
                                  [](const abilities::BoundAbility &) {}},
                       object);
        }
    }
} // namespace dandan::core