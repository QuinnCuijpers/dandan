#include "dandan/costs/CyclingCost.h"
#include "dandan/serialization/JsonFactory.h"

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

    void CyclingCost::pay(core::ExecutionContext exec_ctx,
                          abilities::AbilityContext context) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        m_inner_cost->pay(exec_ctx, context);
        auto player_id{context.controller_id};
        auto &player{game.getPlayer(player_id)};
        auto *card{card_registry[context.source_card_id]};
        player.discardCard(*card, exec_ctx);
    }

} // namespace dandan::costs
