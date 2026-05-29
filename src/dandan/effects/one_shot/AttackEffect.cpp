#include "dandan/effects/one_shot/AttackEffect.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> AttackEffect::apply(
        [[maybe_unused]] core::Game &game) const
    {
        std::cout << "Applying attack effect\n";
        m_creature.setAttacking(true);
        return nullptr;
    }
} // namespace dandan::effects