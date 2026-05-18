#ifndef DANDAN_ENDINGPHASE_H
#define DANDAN_ENDINGPHASE_H

#include "dandan/core/phases/IPhase.h"
#include <cstdint>

// 512. Ending Phase
// 512.1. The ending phase consists of two steps: end and cleanup.

namespace dandan::core
{
    class EndingPhase : public IPhase
    {
    public:
        enum class Step : uint8_t
        {
            End,
            Cleanup,
            Done
        };

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