#include "dandan/effects/one_shot/ChooseCardNameAndMillEffect.h"
#include "dandan/core/Game.h"
#include "dandan/core/PlayerID.h"
#include "dandan/effects/one_shot/MillEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <string>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ChooseCardNameAndMillEffect::apply_impl(
        core::Game &game) const
    {

        auto *card{game.getCardByID(m_source)};
        auto player_id = std::get<core::PlayerID>(m_target);
        std::cout << "Choose a card name, then "
                  << game.getPlayer(player_id).getName() << " mills a card.\n";
        std::cout << "Card Name: ";

        std::string input{};
        std::getline(game.istream(), input);

        card->remember("chosenCardName", input);

        auto mill_effect{std::make_unique<MillEffect>(m_amount, player_id,
                                                      getEffectContext())};
        auto mill_event{mill_effect->apply_impl(game)};
        return mill_event;
    }
} // namespace dandan::effects