#include "dandan/core/Stack.h"
#include "dandan/abilities/SpellAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
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

        auto effect{std::visit(
            overloaded{
                [&game](
                    CardID card_id) -> std::unique_ptr<effects::IOneShotEffect>
                {
                    auto *card{game.getCardByID(card_id)};
                    if (card->getData().getType() == CardData::Type::Instant ||
                        card->getData().getType() == CardData::Type::Sorcery)
                    {
                        for (const auto &ability :
                             card->getData().getAbilities())
                        {
                            // every spell should have one spell ability, so we
                            // can just return the first one we find
                            if (const auto *spell_ability = dynamic_cast<
                                    const abilities::SpellAbility *>(
                                    ability.get()))
                            {
                                abilities::AbilityContext context{
                                    card->getID(), card->getControllerID()};

                                game.moveCardFromZone(
                                    game.getPlayer(card->getControllerID()),
                                    *card);
                                game.graveyard().addCard(*card);
                                auto effect{
                                    spell_ability->createEffect(game, context)};
                                return effect;
                            }
                        }
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
    }
} // namespace dandan::core