#include "dandan/conditions/SelfControlsNoBasicCondition.h"
#include "dandan/core/Game.h"
#include <algorithm>

namespace dandan::conditions
{
    bool SelfControlsNoBasicCondition::isSatisfied(
        [[maybe_unused]] const core::Game &game,
        [[maybe_unused]] std::optional<effects::EffectContext> context) const
    {
        assert(context.has_value());
        auto basic{m_basic_type};
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
            return card != nullptr &&
                   card->getData().getType() == core::CardData::Type::Land &&
                   card->getCurrentSubType() != basic;
        };
        std::cout << "Checking SelfControlsNoBasicCondition for player "
                  << context->player_id.value() << '\n';
        const core::Player &self_player =
            game.getPlayer(context->player_id.value());
        const auto &battlefield{self_player.battlefield()};
        return std::all_of(battlefield.getLands().begin(),
                           battlefield.getLands().end(), no_basic_filter);
    }

} // namespace dandan::conditions