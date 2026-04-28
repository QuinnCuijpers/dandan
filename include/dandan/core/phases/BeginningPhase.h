#ifndef DANDAN_BEGINNINGPHASE_H
#define DANDAN_BEGINNINGPHASE_H

#include "dandan/core/phases/IPhase.h"
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
        BeginningPhase()
        {
            std::cout << "Constructed beginning phase\n";
        };
    };
} // namespace dandan::core
#endif