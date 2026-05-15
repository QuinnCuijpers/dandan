#ifndef DANDAN_MAINPHASE_H
#define DANDAN_MAINPHASE_H

#include "dandan/core/phases/IPhase.h"
#include "dandan/log.h"
// 505. Main Phase
namespace dandan::core
{
    class MainPhase : public IPhase
    {
    public:
        explicit MainPhase(Game &game) : IPhase(game)
        {
            DLOGI << "Constructed main phase\n";
        };

        [[nodiscard]] std::unique_ptr<IPhase> handle() override;
    };
} // namespace dandan::core

#endif