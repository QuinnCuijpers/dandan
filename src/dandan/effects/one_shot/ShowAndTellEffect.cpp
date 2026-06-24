#include "dandan/effects/one_shot/ShowAndTellEffect.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include "dandan/events/IEvent.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ShowAndTellEffect::apply_impl(
        core::Game &game) const
    {

        auto valid_type = [&game, this](const core::CardID card_id)
        {
            auto *card{game.getCardByID(card_id)};
            const auto *fit{std::find(m_types.begin(), m_types.end(),
                                      card->getData().getType())};
            return (fit != m_types.end());
        };

        auto available_options{std::vector<core::CardID>{}};
        auto &player{game.getPlayer(m_player)};
        const auto &hand{player.hand().getCards()};
        std::copy_if(hand.begin(), hand.end(),
                     std::back_inserter(available_options), valid_type);

        game.printCards(available_options);
        std::cout << "You may put an artifact, creature, enchantment, or land "
                     "card from your hand onto the battlefield.\n";
        std::cout << "Which card would you like to put onto the battlefield "
                     "[cardID || -1 for none]: ";
        std::string input{};
        std::getline(game.istream(), input);
        if (input == "-1")
        {
            return nullptr;
        }

        auto card_id{core::CardID::fromInt(std::stoi(input))};

        auto *card{game.getCardByID(card_id)};
        player.playCard(*card);

        return nullptr;
    }
} // namespace dandan::effects