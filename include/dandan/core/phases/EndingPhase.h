#ifndef DANDAN_ENDINGPHASE_H
#define DANDAN_ENDINGPHASE_H

#include "dandan/core/phases/IPhase.h"
#include <cstdint>

// 512. Ending Phase
// 512.1. The ending phase consists of two steps: end and cleanup.

namespace dandan::core
{
    /**
     * Ending Phase
     * @class EndingPhase
     *
     * @implements IPhase
     */
    class EndingPhase : public IPhase
    {
    public:
        /** The steps of the ending phase
         * @enum Step
         */
        // TODO: add CR reference
        enum class Step : uint8_t
        {
            /// The end step, in which "at the end of turn" triggers trigger
            End,
            /// Cleanup step in which damage is removed, cards are discarded to
            /// hand size, etc.
            Cleanup,
            /// Indicates that there are no more steps and we should proceed to
            /// the next phase

            Done
        };

        /**
         * Constructor
         * @param game The game instance.
         */
        explicit EndingPhase(Game &game) : IPhase(game) {};

        [[nodiscard]] std::unique_ptr<IPhase> handle() override;

        [[nodiscard]] std::string name() const override
        {
            return "Ending Phase";
        }

    private:
        Step m_step{Step::End};
        // nullptr is used to indicate that there is no next phase and we should
        // proceed to the next turn
        std::unique_ptr<IPhase> m_next_phase{nullptr};

        void handleNextStep();
    };
} // namespace dandan::core

#endif