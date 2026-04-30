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
        MainPhase(Game *game) : IPhase(game)
        {
            std::cout << "Constructed main phase\n";
        };

        [[nodiscard]] std::unique_ptr<IPhase> handle() override;
    };
} // namespace dandan::core

#endif