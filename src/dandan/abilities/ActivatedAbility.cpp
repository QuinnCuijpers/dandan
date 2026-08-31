#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{
    ActivatedAbility::ActivatedAbility(
        std::unique_ptr<costs::ICost> cost,
        std::unique_ptr<effects::IOneShotEffectDefinition> effect)
        : m_cost(std::move(cost)), m_effect(std::move(effect))
    {
    }

    std::string ActivatedAbility::display() const
    {
        std::string res{};
        if (m_cost)
        {
            res += m_cost->display();
        }
        if (m_effect)
        {
            res += m_effect->display();
        }
        return res;
    }

    // TODO: for now there are no activated abilities with options
    std::string ActivatedAbility::displayOption(
        [[maybe_unused]] size_t index) const
    {
        return display();
    }

    // TODO: for now there are no activated abilities with options
    size_t ActivatedAbility::optionsAmount() const
    {
        return 1;
    }

    std::unique_ptr<effects::IOneShotEffect> ActivatedAbility::createEffect(
        [[maybe_unused]] core::ExecutionContext exec_ctx,
        [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving Activated ability\n";
        m_cost->pay(exec_ctx, context);
        return m_effect->bind(exec_ctx,
                              effects::EffectContext(context.controller_id));
    }
    [[nodiscard]] const costs::ICost *ActivatedAbility::getCost() const
    {
        return m_cost.get();
    }

    [[nodiscard]] const effects::IOneShotEffectDefinition *ActivatedAbility::
        getEffect() const
    {
        return m_effect.get();
    }
    [[nodiscard]] bool ActivatedAbility::canActivate(
        core::ExecutionContext exec_ctx, const AbilityContext &context) const
    {
        auto &card_registry{exec_ctx.cards.get()};
        auto &game{exec_ctx.state.get()};

        if (m_cost)
        {
            const auto *source_card = card_registry[context.source_card_id];
            return m_cost->canPay(
                *source_card, game.getPlayer(source_card->getControllerID()));
        }
        return true;
    }

} // namespace dandan::abilities
