#include "dandan/effects/one_shot/SpinToTopEffect.h"
#include "dandan/core/Game.h"
#include "dandan/core/TargetRequirement.h"

namespace dandan::effects
{
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
        auto &card_registry{exec_ctx.cards.get()};

        if (!std::holds_alternative<core::CardID>(m_target))
        {
            throw std::runtime_error(
                "Spin to top effect target is not a card ID");
        }
        auto permanent{std::get<core::CardID>(m_target)};
        auto *card{card_registry[permanent]};
        game.moveCardFromZone(game.activePlayer(), *card);
        game.library().addCardTop(*card);
        return nullptr;
    }

} // namespace dandan::effects
