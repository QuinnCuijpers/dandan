#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/conditions/SummoningSicknessCondition.h"
#include "dandan/core/Game.h"
#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/events/ETBEvent.h"
#include <memory>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ETBEffect::apply_impl(
        [[maybe_unused]] core::Game &game) const
    {
        auto *card{game.getCardByID(m_card.getID())};

        game.moveCardFromZone(game.getPlayer(card->getControllerID()), m_card);
        std::cout << "Applying ETBEffect\n";
        card->setTapped(m_tapped);
        if (card->getData().getType() == core::CardData::Type::Land)
        {
            game.activePlayer().setPlayedLandThisTurn(true);
        }
        game.activePlayer().battlefield().addCard(*card);

        std::unique_ptr<effects::IPreventionEffect> summoning_sickness{
            std::make_unique<effects::AttackPreventionEffect>(
                std::make_unique<conditions::SummoningSicknessCondition>(
                    card->getID()))};

        game.preventionManager().subscribe(card->getID(),
                                           std::move(summoning_sickness));

        return std::make_unique<events::ETBEvent>(card->getID(),
                                                  card->getControllerID());
    }
} // namespace dandan::effects