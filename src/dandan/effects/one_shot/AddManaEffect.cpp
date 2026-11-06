#include "dandan/effects/one_shot/AddManaEffect.h"
#include "dandan/core/GameState.h"
#include "dandan/core/PriorityManager.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    AddManaEffect::AddManaEffect(mana::ManaBag mana, EffectContext context)
        : IOneShotEffect(std::move(context)), m_mana(std::move(mana))
    {
    }

    std::unique_ptr<IOneShotEffect> AddManaEffect::copy() const
    {
        return std::make_unique<AddManaEffect>(m_mana, getEffectContext());
    }

    std::unique_ptr<events::IEvent> AddManaEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &priority_manager{exec_ctx.priority_manager.get()};

        auto &player{game.getPlayer(priority_manager.getPlayerWithPriority())};
        player.manaPool().add(m_mana);
        return nullptr;
    }

    const mana::ManaBag &AddManaEffect::getMana() const
    {
        return m_mana;
    }
} // namespace dandan::effects
