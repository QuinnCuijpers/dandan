#ifndef DANDAN_COMBATPHASE_H
#define DANDAN_COMBATPHASE_H

#include "dandan/core/phases/IPhase.h"
#include <stdexcept>

// 506. Combat Phase
// 507. Beginning of Combat Step
// 508. Declare Attackers Step
// 509. Declare Blockers Step
// 510. Combat Damage Step
// 511. End of Combat Step

namespace dandan::core
{
    class CombatPhase : public IPhase
    {
    public:
        explicit CombatPhase(Game &game) : IPhase(game) {};

        [[nodiscard]] std::unique_ptr<IPhase> handle() override
        {
            throw std::runtime_error("Combat phase not implemented yet");
        }

        [[nodiscard]] std::string name() const override
        {
            return "Combat Phase";
        }
    };
} // namespace dandan::core

#endif