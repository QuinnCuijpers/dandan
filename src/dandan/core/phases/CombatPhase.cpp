#include "dandan/core/phases/CombatPhase.h"
#include "dandan/core/Game.h"
#include "dandan/core/phases/MainPhase.h"
#include <memory>

namespace dandan::core
{
    CombatPhase::CombatPhase(Game &game)
        : IPhase(game), m_next_phase(std::make_unique<MainPhase>(game, false))
    {
    }

    [[nodiscard]] std::unique_ptr<IPhase> CombatPhase::handle()
    {
        return std::move(m_next_phase);
    }
} // namespace dandan::core
