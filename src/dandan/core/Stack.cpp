#include "dandan/core/Stack.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/SpellAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
#include "dandan/core/CardID.h"
#include "dandan/core/CastContext.h"
#include "dandan/core/GameState.h"
#include "dandan/core/engine/EventManager.h"
#include "dandan/core/engine/ReplacementManager.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/utils/overloadVisitor.h"
#include <memory>

namespace dandan::core
{
    void Stack::push(const StackObject &object)
    {
        std::cout << "Pushing object onto stack\n";
        m_stack.push_back(object);
    }

    [[nodiscard]] bool Stack::isEmpty() const
    {
        return m_stack.empty();
    }

    void Stack::resolveNext(core::ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};
        auto &replacement_manager{exec_ctx.replacement_manager.get()};
        auto &event_manager{exec_ctx.event_manager.get()};

        if (m_stack.empty())
        {
            return;
        }

        auto &object{m_stack.back()};

        std::cout << "Resolving object on stack\n";

        bool resolvingSpell{false};

        auto effect{std::visit(
            utils::overloaded{
                [&resolvingSpell, &card_registry,
                 &exec_ctx](const CastContext &cast_ctx)
                    -> std::unique_ptr<effects::IOneShotEffect>
                {
                    auto *card{card_registry.get(cast_ctx.card_id)};
                    if (card->getData().type == Type::Instant ||
                        card->getData().type == Type::Sorcery)
                    {
                        resolvingSpell = true;

                        auto spell_ability_it{std::find_if(
                            card->getData().abilities.begin(),
                            card->getData().abilities.end(),
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

                        auto effect{
                            spell_ability->createEffect(exec_ctx, context)};
                        return effect;
                    }
                    effects::EffectContext context{card->getControllerID()};
                    return std::make_unique<effects::ETBEffect>(
                        *card_registry.get(card->getID()), context);
                },
                [this, &exec_ctx](const abilities::BoundAbility &ability)
                    -> std::unique_ptr<effects::IOneShotEffect>
                {
                    m_stack.pop_back();
                    return ability.createEffect(exec_ctx);
                }},
            object)};

        if (effect)
        {
            auto final_effect{
                replacement_manager.applyReplacementEffects(*effect, exec_ctx)};
            auto event{final_effect->apply(exec_ctx)};
            if (event)
            {
                std::cout << "Notifying event\n";
                event_manager.notify(*event, exec_ctx);
            }
        }

        // move card to graveyard if it was a spell
        if (resolvingSpell)
        {
            // the stack may have moved in memory so we need to regrab the
            // object
            auto &new_object{m_stack.back()};
            std::cout << "Played spell, so now it gets removed\n";
            std::visit(
                utils::overloaded{
                    [this, &game, &card_registry](const CastContext &cast_ctx)
                    {
                        auto *card{card_registry.get(cast_ctx.card_id)};
                        switch (cast_ctx.mode)
                        {

                        case CastMode::Normal:
                            game.graveyard().addCard(*card);
                            break;
                        case CastMode::Flashback:
                            game.exile().addCard(*card);
                            break;
                        }
                        m_stack.pop_back();
                    },
                    [](const abilities::BoundAbility &) {}},
                new_object);
        }
    }

    [[nodiscard]] const std::vector<StackObject> &Stack::getStackObjects() const
    {
        return m_stack;
    }

    void Stack::removeObject(const StackObject &object)
    {
        m_stack.erase(std::remove_if(m_stack.begin(), m_stack.end(),
                                     [&](const StackObject &stack_object)
                                     { return object == stack_object; }),
                      m_stack.end());
    }
} // namespace dandan::core
