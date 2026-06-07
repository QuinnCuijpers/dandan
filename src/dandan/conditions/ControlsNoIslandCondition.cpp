#include "dandan/conditions/ControlsNoIslandCondition.h"
#include "dandan/core/Battlefield.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
#include "dandan/core/Player.h"
#include <algorithm>

namespace dandan::conditions
{

    bool ControlsNoIslandCondition::isSatisfied(const core::Game &game) const
    {
        std::cout << "Checking ControlsNoIslandCondition\n";
        auto island_filter = [&game](const core::CardID &card_id)
        {
            const auto *card = game.getCardByID(card_id);
            return card != nullptr &&
                   card->getData().getType() == core::CardData::Type::Land &&
                   card->getData().getSubType() ==
                       core::CardData::SubType::Island;
        };
        std::cout << "Checking ControlsNoIslandCondition for player "
                  << game.nonActivePlayer().getID().id() << '\n';
        const core::Player &defending_player = game.nonActivePlayer();
        const auto &battlefield{defending_player.battlefield()};
        return !std::any_of(battlefield.getLands().begin(),
                            battlefield.getLands().end(), island_filter);
    }
} // namespace dandan::conditions