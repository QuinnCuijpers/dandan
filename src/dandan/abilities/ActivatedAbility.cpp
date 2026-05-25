#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{
    std::unique_ptr<effects::IOneShotEffect> ActivatedAbility::createEffect(
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving Activated ability\n";
        m_cost->pay(game, context);
        return m_effect ? m_effect->clone() : nullptr;
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