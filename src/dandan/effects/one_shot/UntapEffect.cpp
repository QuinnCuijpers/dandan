#include "dandan/effects/one_shot//UntapEffect.h"
#include "dandan/events/UntapEvent.h"
#include "dandan/utils/log.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> UntapEffect::apply_impl(
        [[maybe_unused]] core::ExecutionContext exec_ctx) const
    {
        DLOGI << "Untapping " << m_card.getData().name << " with ID "
              << m_card.getID().getID() << "\n";
        m_card.setTapped(false);
        return std::make_unique<events::UntapEvent>(m_card);
    }
} // namespace dandan::effects
