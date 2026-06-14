#include "dandan/effects/one_shot/TutorTopEffect.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include <string>
#include <vector>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> TutorTopEffect::apply_impl(
        core::Game &game) const
    {
        // get all cards matching the filter types
        auto included =
            [&game](const core::CardID &card_id,
                    const std::vector<core::CardData::Type> &filter_types)
        {
            return std::any_of(filter_types.begin(), filter_types.end(),
                               [&card_id, &game](const auto &type)
                               {
                                   auto *card = game.getCardByID(card_id);
                                   return card->getData().getType() == type;
                               });
        };

        std::vector<core::CardID> options{};

        for (const auto &card : game.library().getCards())
        {
            if (included(card, m_filter_types))
            {
                options.push_back(card);
            }
        }

        // ask player which cardid they want
        game.printCards(options);
        std::cout << "Choose a card to put on top of your library: ";
        std::string input;
        std::getline(game.istream(), input);
        int chosen_card_id = std::stoi(input);

        // remove card from lib and shuffle
        const auto *card = game.getCardByID(chosen_card_id);
        game.moveCardFromZone(game.activePlayer(), *card);
        game.library().shuffle();

        // move that card to the top of the library
        game.library().getCards().push_front(
            core::CardID::fromInt(chosen_card_id));

        return nullptr;
    }
} // namespace dandan::effects