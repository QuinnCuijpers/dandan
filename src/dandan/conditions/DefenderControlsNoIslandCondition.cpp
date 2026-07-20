#include "dandan/conditions/DefenderControlsNoBasicCondition.h"
#include "dandan/core/Battlefield.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
#include "dandan/core/Player.h"
#include "dandan/core/SubType.h"
#include "dandan/core/TextReplacement.h"
#include "dandan/effects/EffectContext.h"
#include <algorithm>
#include <optional>
#include <variant>
#include <vector>

namespace dandan::conditions
{

    bool DefenderControlsNoBasicCondition::isSatisfied(
        const core::Game &game,
        [[maybe_unused]] std::optional<effects::EffectContext> context) const
    {
        auto basic{m_type};
        auto text_replacements{context->text_replacements};
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
        auto no_basic_filter = [&](const core::CardID &card_id)
        {
            const auto *card = game.getCardByID(card_id);
            auto subtypes = card->getCurrentSubTypes();
            return card->getData().getType() == core::CardData::Type::Land &&
                   std::all_of(subtypes.begin(), subtypes.end(),
                               [&](core::SubType type)
                               { return basic != type; });
        };
        std::cout << "Checking DefenderControlsNoIslandCondition for player "
                  << game.nonActivePlayer().getID().id() << '\n';
        const core::Player &defending_player = game.nonActivePlayer();
        const auto &battlefield{defending_player.battlefield()};
        return std::all_of(battlefield.getLands().begin(),
                           battlefield.getLands().end(), no_basic_filter);
    }
} // namespace dandan::conditions