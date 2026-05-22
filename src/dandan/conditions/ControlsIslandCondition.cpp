#include "dandan/conditions/ControlsIslandCondition.h"
#include "dandan/core/Battlefield.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
#include "dandan/core/Player.h"
#include <algorithm>

namespace dandan::conditions
{
    bool ControlsIslandCondition::isSatisfied(const core::Game &game)
    {
        auto island_filter = [&game](const core::CardID &card_id)
        {
            const auto *card = game.getCardByID(card_id);
            return card != nullptr &&
                   card->getData().getType() == core::CardData::Type::Land &&
                   card->getData().getSubType() ==
                       core::CardData::SubType::Island;
        };
        const core::Player &current_player = game.nonActivePlayer();
        const auto &battlefield{current_player.battlefield()};
        return std::any_of(battlefield.getLands().begin(),
                           battlefield.getLands().end(), island_filter);
    }
} // namespace dandan::conditions