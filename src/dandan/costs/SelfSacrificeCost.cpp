#include "dandan/costs/SelfSacrificeCost.h"

namespace dandan::costs
{

    std::string SelfSacrificeCost::display(bool isFinal) const
    {
        if (isFinal)
        {
            return "Sacrifice this Card: ";
        }
        return "Sacrifice this Card";
    }

    [[nodiscard]] bool SelfSacrificeCost::canPay(
        const core::Card &source, const core::Player &player) const
    {
        return source.getControllerID().id() == player.getID().id();
    }

    void SelfSacrificeCost::pay(core::ExecutionContext exec_ctx,
                                abilities::AbilityContext context) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        auto &player = game.getPlayer(context.controller_id);
        auto *card = card_registry[context.source_card_id];
        player.sacrificeCard(*card, exec_ctx);
    }

} // namespace dandan::costs
