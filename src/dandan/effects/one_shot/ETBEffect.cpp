#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/core/Game.h"
#include "dandan/events/ETBEvent.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ETBEffect::apply(
        [[maybe_unused]] core::Game &game) const
    {
        std::cout << "Applying ETBEffect\n";
        m_card.setTapped(m_tapped);
        game.activePlayer().battlefield().addCard(m_card);
        return std::make_unique<events::ETBEvent>(m_card.getID(),
                                                  m_card.getControllerID());
    }
} // namespace dandan::effects