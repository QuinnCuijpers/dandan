#include "dandan/effects/one_shot/SelfSacrificeEffect.h"
#include "dandan/core/Card.h"
#include <memory>

namespace dandan::effects
{
    std::unique_ptr<IOneShotEffect> SelfSacrificeEffectDefinition::bind(
        [[maybe_unused]] const core::ExecutionContext exec_ctx,
        [[maybe_unused]] EffectContext context) const
    {
        return std::make_unique<SelfSacrificeEffect>(context.card_id, context);
    }

    std::unique_ptr<IOneShotEffectDefinition> SelfSacrificeEffectDefinition::
        clone() const
    {
        return std::make_unique<SelfSacrificeEffectDefinition>();
    }

    SelfSacrificeEffect::SelfSacrificeEffect(core::CardID card_id,
                                             EffectContext context)
        : IOneShotEffect(std::move(context)), m_card_id(card_id)
    {
    }

    [[nodiscard]] std::unique_ptr<IOneShotEffect> SelfSacrificeEffect::copy()
        const
    {
        return std::make_unique<SelfSacrificeEffect>(m_card_id,
                                                     getEffectContext());
    }

    std::unique_ptr<events::IEvent> SelfSacrificeEffect::apply_impl(
        [[maybe_unused]] core::ExecutionContext exec_ctx) const
    {
        const auto &card_registry{exec_ctx.cards.get()};

        auto *card{card_registry.get(m_card_id)};
        card->destroy(exec_ctx);
        return nullptr;
    }
} // namespace dandan::effects
