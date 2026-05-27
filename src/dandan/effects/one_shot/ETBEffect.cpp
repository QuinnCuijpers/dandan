#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/conditions/SummoningSicknessCondition.h"
#include "dandan/core/Game.h"
#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/events/ETBEvent.h"
#include <memory>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ETBEffect::apply(
        [[maybe_unused]] core::Game &game) const
    {
        game.moveCardFromZone(m_card);
        std::cout << "Applying ETBEffect\n";
        m_card.setTapped(m_tapped);
        if (m_card.getData().getType() == core::CardData::Type::Land)
        {
            game.activePlayer().setPlayedLandThisTurn(true);
        }
        game.activePlayer().battlefield().addCard(m_card);

        std::unique_ptr<effects::IPreventionEffect> summoning_sickness{
            std::make_unique<effects::AttackPreventionEffect>(
                std::make_unique<conditions::SummoningSicknessCondition>(
                    m_card))};

        game.preventionManager().subscribe(std::move(summoning_sickness));
        return std::make_unique<events::ETBEvent>(m_card.getID(),
                                                  m_card.getControllerID());
    }
} // namespace dandan::effects