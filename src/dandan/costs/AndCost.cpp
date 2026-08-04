#include "dandan/costs/AndCost.h"

namespace dandan::costs
{

    AndCost::AndCost(std::unique_ptr<ICost> first,
                     std::unique_ptr<ICost> second)
        : m_first(std::move(first)), m_second(std::move(second))
    {
    }

    std::string AndCost::display(bool isFinal) const
    {
        std::string res{};
        res += m_first->display(false);
        res += ", ";
        res += m_second->display(isFinal);
        return res;
    }

    [[nodiscard]] std::vector<ICost *> AndCost::getCosts() const
    {
        return {m_first.get(), m_second.get()};
    }

    void AndCost::pay(core::Game &game, abilities::AbilityContext context) const
    {
        m_first->pay(game, context);
        m_second->pay(game, context);
    }

    [[nodiscard]] bool AndCost::canPay(const core::Card &source,
                                       const core::Player &player) const
    {
        return m_first->canPay(source, player) &&
               m_second->canPay(source, player);
    }

} // namespace dandan::costs
