#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{
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
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving Activated ability\n";
        m_cost->pay(game, context);
        return m_effect->bind(game,
                              effects::EffectContext(context.controller_id));
    }

    [[nodiscard]] bool ActivatedAbility::canActivate(
        core::Game &game, AbilityContext context) const
    {
        if (m_cost)
        {
            auto *source_card = game.getCardByID(context.source_card_id);
            return m_cost->canPay(
                *source_card, game.getPlayer(source_card->getControllerID()));
        }
        return true;
    }

} // namespace dandan::abilities