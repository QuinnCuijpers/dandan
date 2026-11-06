#include "dandan/effects/one_shot/ChooseCardNameAndMillEffect.h"
#include "dandan/core/GameState.h"
#include "dandan/core/PlayerID.h"
#include "dandan/effects/one_shot/MillEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <string>
#include <utility>

namespace dandan::effects
{
    ChooseCardNameAndMillEffect::ChooseCardNameAndMillEffect(
        int amount, core::CardID card_id, core::Target target,
        EffectContext effect_context)
        : IOneShotEffect(std::move(effect_context)), m_amount(amount),
          m_source(card_id), m_target(std::move(target))
    {
    }

    std::unique_ptr<IOneShotEffect> ChooseCardNameAndMillEffect::copy() const
    {
        return std::make_unique<ChooseCardNameAndMillEffect>(
            m_amount, m_source, m_target, getEffectContext());
    }

    ChooseCardNameAndMillEffectDefinition::
        ChooseCardNameAndMillEffectDefinition(
            core::TargetRequirement target_reqs)
        : m_target_requirements(std::move(target_reqs))
    {
    }

    ChooseCardNameAndMillEffectDefinition::
        ChooseCardNameAndMillEffectDefinition(
            int amount, core::TargetRequirement target_reqs)
        : m_amount(amount), m_target_requirements(std::move(target_reqs))
    {
    }

    std::unique_ptr<IOneShotEffect> ChooseCardNameAndMillEffectDefinition::bind(
        [[maybe_unused]] const core::ExecutionContext exec_ctx,
        [[maybe_unused]] EffectContext context) const
    {
        const auto &card_registry{exec_ctx.cards.get()};
        const auto *source_card{card_registry.get(context.card_id)};

        auto choices{source_card->getTargetChoices(*this)};
        auto choice{choices.at(0)};

        return std::make_unique<ChooseCardNameAndMillEffect>(
            m_amount, source_card->getID(), choice, context);
    }

    std::unique_ptr<IOneShotEffectDefinition>
    ChooseCardNameAndMillEffectDefinition::clone() const
    {
        return std::make_unique<ChooseCardNameAndMillEffectDefinition>(
            m_amount, m_target_requirements);
    }

    int ChooseCardNameAndMillEffectDefinition::getAmount() const
    {
        return m_amount;
    }

    const core::TargetRequirement *ChooseCardNameAndMillEffectDefinition::
        getTargetRequirement() const
    {
        return &m_target_requirements;
    }

    std::unique_ptr<events::IEvent> ChooseCardNameAndMillEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {

        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        auto *card{card_registry.get(m_source)};
        auto player_id = std::get<core::PlayerID>(m_target);
        std::cout << "Choose a card name, then "
                  << game.getPlayer(player_id).getName() << " mills a card.\n";
        std::cout << "Card Name: ";

        std::string input{};
        std::getline(istream, input);

        card->remember("chosenCardName", input);

        auto mill_effect{std::make_unique<MillEffect>(m_amount, player_id,
                                                      getEffectContext())};
        auto mill_event{mill_effect->apply_impl(exec_ctx)};
        return mill_event;
    }
} // namespace dandan::effects
