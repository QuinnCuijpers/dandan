#include "dandan/costs/CyclingCost.h"

namespace dandan::costs
{

    CyclingCost::CyclingCost(std::unique_ptr<ICost> inner_cost)
        : m_inner_cost{std::move(inner_cost)} {};

    std::string CyclingCost::display(bool isFinal) const
    {
        std::string res{};
        res += m_inner_cost->display(isFinal);
        res += ", Discard this card: ";
        return res;
    }

    /** Gets the inner cost.
     * @return A pointer to the inner cost.
     */
    [[nodiscard]] const ICost *CyclingCost::getInnerCost() const
    {
        return m_inner_cost.get();
    }

    [[nodiscard]] bool CyclingCost::canPay(const core::Card &source,
                                           const core::Player &player) const
    {
        if (source.getZone() != core::Zone::HAND)
        {
            return false;
        }
        return m_inner_cost->canPay(source, player);
    }

    void CyclingCost::pay(core::Game &game,
                          abilities::AbilityContext context) const
    {
        m_inner_cost->pay(game, context);
        auto player_id{context.controller_id};
        auto &player{game.getPlayer(player_id)};
        auto *card{game.getCardByID(context.source_card_id)};
        player.discardCard(*card, game);
    }

} // namespace dandan::costs
