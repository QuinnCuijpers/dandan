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

    void TapCost::pay(core::ExecutionContext exec_ctx,
                      abilities::AbilityContext context) const
    {
        auto &card_registry{exec_ctx.cards.get()};

        auto *card = card_registry[context.source_card_id];
        card->setTapped(true);
    }

} // namespace dandan::costs
