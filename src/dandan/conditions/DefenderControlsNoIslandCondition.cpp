#include "dandan/conditions/DefenderControlsNoBasicCondition.h"
#include "dandan/core/Battlefield.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
#include "dandan/core/Player.h"
#include "dandan/core/SubType.h"
#include "dandan/core/TextReplacement.h"
#include <algorithm>
#include <optional>
#include <variant>
#include <vector>

namespace dandan::conditions
{

    bool DefenderControlsNoBasicCondition::isSatisfied(
        const core::Game &game,
        [[maybe_unused]] std::optional<std::vector<core::TextReplacement>>
            text_replacements) const
    {
        std::cout << "Checking ControlsNoIslandCondition\n";
        auto basic{m_type};
        if (text_replacements.has_value())
        {
            auto text_replacements_v{text_replacements.value()};
            for (const auto &replacement : text_replacements_v)
            {
                if (std::holds_alternative<core::SubType>(replacement.from) &&
                    std::holds_alternative<core::SubType>(replacement.to))
                {
                    auto from = std::get<core::SubType>(replacement.from);
                    auto new_ = std::get<core::SubType>(replacement.to);
                    if (basic == from)
                    {
                        basic = new_;
                    }
                }
            }
        }
        auto no_basic_filter = [&game, this](const core::CardID &card_id)
        {
            const auto *card = game.getCardByID(card_id);
            return card != nullptr &&
                   card->getData().getType() == core::CardData::Type::Land &&
                   card->getData().getSubType() != m_type;
        };
        std::cout << "Checking ControlsNoIslandCondition for player "
                  << game.nonActivePlayer().getID().id() << '\n';
        const core::Player &defending_player = game.nonActivePlayer();
        const auto &battlefield{defending_player.battlefield()};
        return std::all_of(battlefield.getLands().begin(),
                           battlefield.getLands().end(), no_basic_filter);
    }
} // namespace dandan::conditions