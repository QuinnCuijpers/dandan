#include "dandan/effects/one_shot/TutorTopEffect.h"
#include "dandan/core/CardID.h"
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> TutorTopEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        // get all cards matching the filter types
        auto included =
            [&card_registry](const core::CardID &card_id,
                             const std::vector<core::Type> &filter_types)
        {
            return std::any_of(filter_types.begin(), filter_types.end(),
                               [&card_id, &card_registry](const auto &type)
                               {
                                   const auto *card = card_registry[card_id];
                                   return card->getData().type == type;
                               });
        };

        std::vector<core::CardID> options{};

        std::copy_if(game.library().getCards().begin(),
                     game.library().getCards().end(),
                     std::back_inserter(options), [&](const auto &card)
                     { return included(card, m_filter_types); });

        // ask player which cardid they want
        game.printCards(options, card_registry);
        std::cout << "Choose a card to put on top of your library: ";
        std::string input;
        std::getline(istream, input);
        int chosen_card_id = std::stoi(input);

        // remove card from lib and shuffle
        const auto *card = card_registry[chosen_card_id];
        game.moveCardFromZone(game.activePlayer(), *card);
        game.library().shuffle();

        // move that card to the top of the library
        game.library().getCards().push_front(
            core::CardID::fromInt(chosen_card_id));

        return nullptr;
    }
} // namespace dandan::effects
