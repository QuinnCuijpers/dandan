#include "dandan/effects/one_shot/AddManaEffect.h"
#include "dandan/core/GameState.h"
#include "dandan/core/PriorityManager.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> AddManaEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &priority_manager{exec_ctx.priority_manager.get()};

        auto &player{game.getPlayer(priority_manager.getPlayerWithPriority())};
        player.manaPool().add(m_mana);
        return nullptr;
    }
} // namespace dandan::effects
