#ifndef DANDAN_MAINPHASE_H
#define DANDAN_MAINPHASE_H

#include "dandan/core/phases/IPhase.h"
#include <memory>

// 505. Main Phase
namespace dandan::core
{
    class CombatPhase;
    class EndingPhase;

    class MainPhase : public IPhase
    {
    public:

        explicit MainPhase(Game &game);

        MainPhase(Game &game, bool pre_combat);

        [[nodiscard]] std::unique_ptr<IPhase> handle() override;

        [[nodiscard]] std::string name() const override
        {
            return "Main Phase";
        }

    private:
        std::unique_ptr<IPhase> m_next_phase;
        bool m_pre_combat_main_phase{true};
    };
} // namespace dandan::core

#endif