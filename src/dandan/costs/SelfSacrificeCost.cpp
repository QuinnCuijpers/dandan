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

    void SelfSacrificeCost::pay(core::Game &game,
                                abilities::AbilityContext context) const
    {
        [[maybe_unused]] auto &player = game.getPlayer(context.controller_id);
        auto *card = game.getCardByID(context.source_card_id);
        player.sacrificeCard(*card, game);
    }

} // namespace dandan::costs
