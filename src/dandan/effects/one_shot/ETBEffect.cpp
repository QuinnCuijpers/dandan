#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/conditions/SummoningSicknessCondition.h"
#include "dandan/core/GameState.h"
#include "dandan/core/engine/PreventionManager.h"
#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/events/ETBEvent.h"
#include <memory>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ETBEffect::apply_impl(
        [[maybe_unused]] core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};
        auto &prevention_manager{exec_ctx.prevention_manager.get()};

        auto *card{card_registry[m_card.getID()]};

        game.moveCardFromZone(game.getPlayer(card->getControllerID()), m_card);
        std::cout << "Applying ETBEffect\n";
        card->setTapped(m_tapped);
        if (card->getData().type == core::Type::Land)
        {
            game.activePlayer().setPlayedLandThisTurn(true);
        }
        game.activePlayer().battlefield().addCard(*card);

        std::unique_ptr<effects::IPreventionEffect> summoning_sickness{
            std::make_unique<effects::AttackPreventionEffect>(
                std::make_unique<conditions::SummoningSicknessCondition>(
                    card->getID()))};

        prevention_manager.subscribe(card->getID(),
                                     std::move(summoning_sickness));

        return std::make_unique<events::ETBEvent>(card->getID(),
                                                  card->getControllerID());
    }
} // namespace dandan::effects
