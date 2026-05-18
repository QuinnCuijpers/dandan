#ifndef DANDAN_BEGINNINGPHASE_H
#define DANDAN_BEGINNINGPHASE_H

#include "dandan/core/phases/IPhase.h"
#include "dandan/core/phases/MainPhase.h"
#include <cstdint>
#include <memory>

// 501. Beginning Phase
// 502. Untap Step
// 503. Upkeep Step
// 504. Draw Step

namespace dandan::core
{
    class BeginningPhase : public IPhase
    {
    public:
        enum class Step : uint8_t
        {
            Untap,
            Upkeep,
            Draw,
            Done
        };

        explicit BeginningPhase(Game &game) : IPhase(game) {};

        void setStep(Step step)
        {
            m_step = step;
        }

        std::unique_ptr<IPhase> handle() override;

        [[nodiscard]] std::string name() const override
        {
            return "Beginning Phase";
        }

    private:
        Step m_step{Step::Untap};
        std::unique_ptr<IPhase> m_next_phase{
            std::make_unique<MainPhase>(game())};

        void handleNextStep();
    };
} // namespace dandan::core
#endif