#ifndef DANDAN_MAINPHASE_H
#define DANDAN_MAINPHASE_H

#include "dandan/core/phases/IPhase.h"
#include <iostream>
// 505. Main Phase
namespace dandan::core
{
    class MainPhase : public IPhase
    {
    public:
        MainPhase()
        {
            std::cout << "Constructed main phase\n";
        };
    };
} // namespace dandan::core

#endif