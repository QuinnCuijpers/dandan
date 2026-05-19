#include "dandan/effects/one_shot//UntapEffect.h"
#include "dandan/events/UntapEvent.h"
#include "dandan/log.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> UntapEffect::apply(
        [[maybe_unused]] core::Game &game) const
    {
        DLOGI << "Untapping " << m_card.getData().getName() << " with ID "
              << m_card.getID().getID() << "\n";
        m_card.setTapped(false);
        return std::make_unique<events::UntapEvent>(m_card);
    }
} // namespace dandan::effects