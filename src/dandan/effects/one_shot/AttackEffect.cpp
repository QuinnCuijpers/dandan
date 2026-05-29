#include "dandan/effects/one_shot/AttackEffect.h"
#include "dandan/core/Game.h"
#include "dandan/core/phases/CombatPhase.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> AttackEffect::apply(
        [[maybe_unused]] core::Game &game) const
    {
        std::cout << "Applying attack effect\n";
        if (auto *combat_phase{
                dynamic_cast<core::CombatPhase *>(game.phase().get())};
            combat_phase != nullptr)
        {
            m_creature.setAttacking(true);
            combat_phase->addAttacker(&m_creature);
        }
        // should add check for vigilance but its not relevant in dandan
        m_creature.setTapped(true);
        return nullptr;
    }
} // namespace dandan::effects