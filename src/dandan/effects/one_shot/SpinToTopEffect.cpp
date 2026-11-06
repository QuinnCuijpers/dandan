#include "dandan/effects/one_shot/SpinToTopEffect.h"
#include "dandan/core/Game.h"
#include "dandan/core/TargetRequirement.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    SpinToTopEffectDefinition::SpinToTopEffectDefinition(
        core::TargetRequirement target_req)
        : m_target_requirements(std::move(target_req))
    {
    }

    std::unique_ptr<IOneShotEffect> SpinToTopEffectDefinition::bind(
        const core::ExecutionContext exec_ctx, EffectContext context) const
    {
        const auto &card_registry{exec_ctx.cards.get()};
        const auto *card{card_registry.get(context.card_id)};
        auto choices{card->getTargetChoices(*this)};
        auto choice{choices.at(0)};
        return std::make_unique<SpinToTopEffect>(choice, context);
    }

    std::unique_ptr<IOneShotEffectDefinition> SpinToTopEffectDefinition::clone()
        const
    {
        return std::make_unique<SpinToTopEffectDefinition>(
            m_target_requirements);
    }

    const core::TargetRequirement *SpinToTopEffectDefinition::
        getTargetRequirement() const
    {
        return &m_target_requirements;
    }

    SpinToTopEffect::SpinToTopEffect(core::Target target, EffectContext context)
        : IOneShotEffect(std::move(context)), m_target(std::move(target))
    {
    }

    [[nodiscard]] std::unique_ptr<IOneShotEffect> SpinToTopEffect::copy() const
    {
        return std::make_unique<SpinToTopEffect>(m_target, getEffectContext());
    }

    std::unique_ptr<events::IEvent> SpinToTopEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        if (!std::holds_alternative<core::CardID>(m_target))
        {
            throw std::runtime_error(
                "Spin to top effect target is not a card ID");
        }
        auto permanent{std::get<core::CardID>(m_target)};
        auto *card{card_registry.get(permanent)};
        game.moveCardFromZone(game.activePlayer(), *card);
        game.library().addCardTop(*card);
        return nullptr;
    }

} // namespace dandan::effects
