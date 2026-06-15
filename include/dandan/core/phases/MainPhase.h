#ifndef DANDAN_MAINPHASE_H
#define DANDAN_MAINPHASE_H

#include "dandan/core/phases/IPhase.h"
#include <memory>

// 505. Main Phase
namespace dandan::core
{
    class CombatPhase;
    class EndingPhase;
    // TODO: improve docs for main phase and add more details about what happens
    // in the main phase, and what actions can be taken, etc.
    /**
     * @brief Main Phase
     * @class MainPhase
     *
     * @implements IPhase
     */
    class MainPhase : public IPhase
    {
    public:
        /** Constructor, pre_combat defaults to true, as the first main phase of
         * the turn is the pre-combat main phase
         *
         * @param game The game instance.
         */
        explicit MainPhase(Game &game);

        /** Constructor
         * @param game The game instance.
         * @param pre_combat Whether this is a pre-combat main phase.
         */
        MainPhase(Game &game, bool pre_combat);

        [[nodiscard]] std::unique_ptr<IPhase> handle() override;

        [[nodiscard]] std::string name() const override
        {
            return "Main Phase";
        }

    private:
        std::unique_ptr<IPhase> m_next_phase;
        bool m_pre_combat_main_phase{true};
    };
} // namespace dandan::core

#endif
