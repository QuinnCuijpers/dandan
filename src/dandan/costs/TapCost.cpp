#include "dandan/costs/TapCost.h"

namespace dandan::costs
{
    std::string TapCost::display(bool isFinal) const
    {
        if (isFinal)
        {
            return "[T]: ";
        }
        return "[T]";
    }

    [[nodiscard]] bool TapCost::canPay(
        const core::Card &source,
        [[maybe_unused]] const core::Player &player) const
    {
        return !source.getTapped() &&
               source.getZone() == core::Zone::BATTLEFIELD;
    }

    void TapCost::pay(core::Game &game, abilities::AbilityContext context) const
    {
        auto *card = game.getCardByID(context.source_card_id);
        card->setTapped(true);
    }

} // namespace dandan::costs
