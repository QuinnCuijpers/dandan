#include "dandan/effects/one_shot/MemoryLapseEffect.h"
#include "dandan/core/Game.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    MemoryLapseEffect::MemoryLapseEffect(core::Target target,
                                         EffectContext context,
                                         core::Zone target_zone)
        : IOneShotEffect(std::move(context)), m_target(std::move(target)),
          m_target_zone(target_zone)
    {
    }

    std::unique_ptr<IOneShotEffect> MemoryLapseEffect::copy() const
    {
        return std::make_unique<MemoryLapseEffect>(m_target,
                                                   getEffectContext());
    }

    MemoryLapseEffectDefinition::MemoryLapseEffectDefinition(
        core::TargetRequirement target_requirements)
        : m_target_requirements(std::move(target_requirements))
    {
    }

    std::unique_ptr<IOneShotEffect> MemoryLapseEffectDefinition::bind(
        const core::ExecutionContext exec_ctx, EffectContext context) const
    {
        const auto &card_registry{exec_ctx.cards.get()};
        const auto *card{card_registry.get(context.card_id)};
        auto choices{card->getTargetChoices(*this)};
        auto choice{choices.at(0)};
        return std::make_unique<MemoryLapseEffect>(choice, context);
    }

    std::unique_ptr<IOneShotEffectDefinition> MemoryLapseEffectDefinition::
        clone() const
    {
        return std::make_unique<MemoryLapseEffectDefinition>(
            m_target_requirements);
    }

    const core::TargetRequirement *MemoryLapseEffectDefinition::
        getTargetRequirement() const
    {
        return &m_target_requirements;
    }

    std::unique_ptr<events::IEvent> MemoryLapseEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        if (!std::holds_alternative<core::CardID>(m_target))
        {
            throw std::runtime_error(
                "MemoryLapseEffect target is not a CardID");
        }
        auto card_id{std::get<core::CardID>(m_target)};
        auto *card{card_registry.get(card_id)};
        auto &controller{game.getPlayer(card->getControllerID())};

        if (card->canBeCountered())
        {
            game.moveCardFromZone(controller, *card);
            game.moveCardToZone(*card, controller, m_target_zone);
        }
        return nullptr;
    }
} // namespace dandan::effects
