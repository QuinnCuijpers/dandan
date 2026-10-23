#include "dandan/effects/one_shot/MillEffect.h"
#include "dandan/core/GameState.h"
#include "dandan/utils/convertToWords.h"
#include <memory>
#include <utility>
#include <variant>

namespace dandan::effects
{
    MillEffect::MillEffect(int amount, core::PlayerID player_id,
                           EffectContext context)
        : IOneShotEffect(std::move(context)), m_amount(amount),
          m_player_id(player_id)
    {
    }

    std::unique_ptr<IOneShotEffect> MillEffect::copy() const
    {
        return std::make_unique<MillEffect>(m_amount, m_player_id,
                                            getEffectContext());
    }

    MillEffectDefinition::MillEffectDefinition(
        int amount, core::TargetRequirement target_requirement)
        : m_amount(amount), m_target_requirement(std::move(target_requirement))
    {
    }

    std::unique_ptr<IOneShotEffect> MillEffectDefinition::bind(
        const core::ExecutionContext exec_ctx,
        [[maybe_unused]] EffectContext context) const
    {
        const auto &card_registry{exec_ctx.cards.get()};
        const auto *card{card_registry.get(context.card_id)};
        auto choices{card->getTargetChoices(*this)};
        auto choice{choices.at(0)};
        auto player_choice{std::get<core::PlayerID>(choice)};
        return std::make_unique<MillEffect>(m_amount, player_choice, context);
    }

    std::unique_ptr<IOneShotEffectDefinition> MillEffectDefinition::clone()
        const
    {
        return std::make_unique<MillEffectDefinition>(m_amount,
                                                      m_target_requirement);
    }

    int MillEffectDefinition::getAmount() const
    {
        return m_amount;
    }

    const core::TargetRequirement *MillEffectDefinition::getTargetRequirement()
        const
    {
        return &m_target_requirement;
    }

    std::unique_ptr<events::IEvent> MillEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        auto context{getEffectContext()};
        auto milled_cards{game.library().mill(exec_ctx, m_amount)};
        auto card_id{context.card_id};
        if (milled_cards.size() == 1)
        {
            auto *card{card_registry.get(card_id)};
            auto milled_id{milled_cards[0]};
            const auto &name{card_registry.get(milled_id)->getData().name};
            card->remember("milledCardName", name);
        }
        return nullptr;
    }

    std::string MillEffectDefinition::display() const
    {
        return "Target player mills " + utils::convertToWords(m_amount) +
               " card" + (m_amount > 1 ? "s" : "");
    }
} // namespace dandan::effects
