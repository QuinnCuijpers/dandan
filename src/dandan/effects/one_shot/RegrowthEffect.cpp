#include "dandan/effects/one_shot/RegrowthEffect.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/GameState.h"
#include "dandan/events/IEvent.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> RegrowthEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        // get all cards matching the filter types
        auto included =
            [&card_registry](const core::CardID &card_id,
                             const std::vector<core::Type> &filter_types)
        {
            return std::any_of(filter_types.begin(), filter_types.end(),
                               [&card_id, &card_registry](const auto &type)
                               {
                                   const auto *card =
                                       card_registry.get(card_id);
                                   return card->getData().type == type;
                               });
        };

        std::vector<core::CardID> options{};

        std::copy_if(game.graveyard().getCards().begin(),
                     game.graveyard().getCards().end(),
                     std::back_inserter(options), [&](const auto &card)
                     { return included(card, m_filter_types); });

        // ask player which cardid they want
        core::GameState::printCards(options, card_registry);
        std::cout << "Choose a cardID to retrieve from the graveyard: ";
        std::string input;
        std::getline(istream, input);
        int chosen_card_id = std::stoi(input);

        auto &player{game.getPlayer(m_player_id)};

        auto *card = card_registry.get(chosen_card_id);
        game.moveCardFromZone(player, *card);

        player.hand().addCard(*card);

        return nullptr;
    }
} // namespace dandan::effects
