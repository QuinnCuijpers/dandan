#include "dandan/effects/one_shot/MillEffect.h"
#include "dandan/utils/convertToWords.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> MillEffect::apply_impl(
        core::Game &game) const
    {
        auto context{getEffectContext()};
        auto milled_cards{game.library().mill(game, m_amount)};
        if (context.card_id.has_value())
        {
            auto card_id{context.card_id.value()};
            auto *card{game.getCardByID(card_id)};
            if (milled_cards.size() == 1)
            {
                auto milled_id{milled_cards[0]};
                auto name{game.getCardByID(milled_id)->getData().getName()};
                card->remember("milledCardName", name);
            }
        }
        return nullptr;
    }

    std::string MillEffectDefinition::display() const
    {
        return "Target player mills " + utils::convertToWords(m_amount) +
               " card" + (m_amount > 1 ? "s" : "");
    }
} // namespace dandan::effects