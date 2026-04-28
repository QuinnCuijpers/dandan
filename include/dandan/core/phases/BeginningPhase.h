#ifndef DANDAN_BEGINNINGPHASE_H
#define DANDAN_BEGINNINGPHASE_H

#include "dandan/core/phases/IPhase.h"
#include <cstdint>
#include <iostream>

// 501. Beginning Phase
// 502. Untap Step
// 503. Upkeep Step
// 504. Draw Step

namespace dandan::core
{
    class BeginningPhase : public IPhase
    {
    public:
        enum Step : uint8_t
        {
            Untap,
            Upkeep,
            Draw
        };

        explicit BeginningPhase(Game *game) : IPhase(game)
        {
            std::cout << "Constructed beginning phase\n";
        };

        void setStep(Step step)
        {
            m_step = step;
        }

        void handle();

    private:
        Step m_step{Step::Untap};
    };
} // namespace dandan::core
#endif