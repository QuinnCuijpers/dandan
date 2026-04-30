#ifndef DANDAN_ENDINGPHASE_H
#define DANDAN_ENDINGPHASE_H

#include "dandan/core/phases/IPhase.h"
#include <iostream>

// 512. Ending Phase
// 513. End Step
// 514. Cleanup Step -->

namespace dandan::core
{
    class EndingPhase : public IPhase
    {
    public:
        EndingPhase(Game *game) : IPhase(game)
        {
            std::cout << "Constructed ending phase\n";
        };

        [[nodiscard]] std::unique_ptr<IPhase> handle() override;
    };
} // namespace dandan::core

#endif