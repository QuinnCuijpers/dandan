#ifndef DANDAN_MAINPHASE_H
#define DANDAN_MAINPHASE_H

#include "dandan/core/phases/CombatPhase.h"
#include "dandan/core/phases/IPhase.h"
// 505. Main Phase
namespace dandan::core
{
    class MainPhase : public IPhase
    {
    public:
        explicit MainPhase(Game &game) : IPhase(game) {};

        [[nodiscard]] std::unique_ptr<IPhase> handle() override;

        [[nodiscard]] std::string name() const override
        {
            return "Main Phase";
        }

    private:
        std::unique_ptr<IPhase> m_next_phase{
            std::make_unique<CombatPhase>(game())};
    };
} // namespace dandan::core

#endif