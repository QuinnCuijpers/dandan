#ifndef DANDAN_MAINPHASE_H
#define DANDAN_MAINPHASE_H

#include "dandan/core/phases/IPhase.h"
#include <memory>

// 505. Main Phase
namespace dandan::core
{
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
        /** Constructor
         * @param game The game instance.
         * @param pre_combat Whether this is a pre-combat main phase. Defaults
         * to true.
         */
        explicit MainPhase(Game &game, bool pre_combat = true);

        /** Constructor
         * @param game The game instance.
         * @param pre_combat Whether this is a pre-combat main phase.
         */

        [[nodiscard]] std::unique_ptr<IPhase> handle() override;

        [[nodiscard]] std::string name() const override;

    private:
        std::unique_ptr<IPhase> m_next_phase;
        bool m_pre_combat_main_phase{true};
    };
} // namespace dandan::core

#endif
