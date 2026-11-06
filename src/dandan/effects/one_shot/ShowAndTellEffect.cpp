#include "dandan/effects/one_shot/ShowAndTellEffect.h"
#include "dandan/core/CardID.h"
#include "dandan/core/GameState.h"
#include "dandan/events/IEvent.h"
#include <algorithm>
#include <array>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace dandan::effects
{
    ShowAndTellEffect::ShowAndTellEffect(core::PlayerID player_id,
                                         EffectContext context)
        : IOneShotEffect(std::move(context)), m_player(player_id)
    {
    }

    std::unique_ptr<IOneShotEffect> ShowAndTellEffect::copy() const
    {
        return std::make_unique<ShowAndTellEffect>(m_player,
                                                   getEffectContext());
    }

    ShowAndTellEffectDefinition::ShowAndTellEffectDefinition(
        core::TargetRequirement target_requirement)
        : m_target_requirements(std::move(target_requirement))
    {
    }

    std::unique_ptr<IOneShotEffect> ShowAndTellEffectDefinition::bind(
        [[maybe_unused]] const core::ExecutionContext exec_ctx,
        EffectContext context) const
    {
        auto player_id{context.player_id};
        return std::make_unique<ShowAndTellEffect>(player_id, context);
    }

    std::unique_ptr<IOneShotEffectDefinition> ShowAndTellEffectDefinition::
        clone() const
    {
        return std::make_unique<ShowAndTellEffectDefinition>(
            m_target_requirements);
    }

    const core::TargetRequirement *ShowAndTellEffectDefinition::
        getTargetRequirement() const
    {
        return &m_target_requirements;
    }

    std::unique_ptr<events::IEvent> ShowAndTellEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        auto valid_type = [this, &card_registry](const core::CardID card_id)
        {
            auto *card{card_registry.get(card_id)};
            const auto *fit{std::find(m_types.begin(), m_types.end(),
                                      card->getData().type)};
            return (fit != m_types.end());
        };

        auto available_options{std::vector<core::CardID>{}};
        auto &player{game.getPlayer(m_player)};
        const auto &hand{player.hand().getCards()};
        std::copy_if(hand.begin(), hand.end(),
                     std::back_inserter(available_options), valid_type);

        core::GameState::printCards(available_options, card_registry);
        std::cout << "You may put an artifact, creature, enchantment, or land "
                     "card from your hand onto the battlefield.\n";
        std::cout << "Which card would you like to put onto the battlefield "
                     "[cardID || -1 for none]: ";
        std::string input{};
        std::getline(istream, input);
        if (input == "-1")
        {
            return nullptr;
        }

        auto card_id{core::CardID::fromInt(std::stoi(input))};

        auto *card{card_registry.get(card_id)};
        player.playCard(*card);

        return nullptr;
    }
} // namespace dandan::effects
