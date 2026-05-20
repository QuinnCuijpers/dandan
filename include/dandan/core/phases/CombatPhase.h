#ifndef DANDAN_COMBATPHASE_H
#define DANDAN_COMBATPHASE_H

#include "dandan/core/phases/IPhase.h"

// 506. Combat Phase
// 507. Beginning of Combat Step
// 508. Declare Attackers Step
// 509. Declare Blockers Step
// 510. Combat Damage Step
// 511. End of Combat Step

namespace dandan::core
{
    class MainPhase;

    /**
     * Combat Phase
     * @class CombatPhase
     *
     * @implements IPhase
     */
    class CombatPhase : public IPhase
    {
    public:
        /** Constructor
         * @param game The game instance.
         */
        explicit CombatPhase(Game &game);

        [[nodiscard]] std::unique_ptr<IPhase> handle() override;

        [[nodiscard]] std::string name() const override
        {
            return "Combat Phase";
        }

    private:
        std::unique_ptr<IPhase> m_next_phase;
    };
} // namespace dandan::core

#endif