#ifndef DANDAN_COMBATPHASE_H
#define DANDAN_COMBATPHASE_H

#include "dandan/core/phases/IPhase.h"
#include <cstdint>

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
     * @brief Combat Phase
     * @class CombatPhase
     *
     * @implements IPhase
     */
    class CombatPhase : public IPhase
    {
    public:
        /** The steps of the combat phase
         * @enum Step
         */
        enum class Step : uint8_t
        {
            /// The beginning of combat step, in which "at the beginning of
            /// combat" triggers trigger
            BeginningOfCombat,
            /// The declare attackers step, in which players declare their
            /// attackers and "when you declare an attacker" triggers trigger
            DeclareAttackers,
            /// The declare blockers step, in which players declare their
            /// blockers and "when you declare a blocker" triggers trigger
            DeclareBlockers,
            /// The combat damage step, in which damage is dealt and "when
            /// damage is dealt" triggers trigger
            CombatDamage,
            /// The end of combat step, in which "at the end of combat" triggers
            /// trigger and players can activate combat effects before going to
            /// the next phase
            EndOfCombat,
            /// Indicates that there are no more steps and we should proceed to
            /// the next phase
            Done
        };

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
        Step m_step{Step::BeginningOfCombat};
        std::unique_ptr<IPhase> m_next_phase;

        void handleNextStep();
    };
} // namespace dandan::core

#endif
