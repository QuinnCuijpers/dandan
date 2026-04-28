#ifndef DANDAN_COMBATPHASE_H
#define DANDAN_COMBATPHASE_H

#include <iostream>

// 506. Combat Phase
// 507. Beginning of Combat Step
// 508. Declare Attackers Step
// 509. Declare Blockers Step
// 510. Combat Damage Step
// 511. End of Combat Step

namespace dandan::core
{
    class CombatPhase
    {
    public:
        CombatPhase()
        {
            std::cout << "Constructed combat phase\n";
        };
    };
} // namespace dandan::core

#endif