#include "dandan/costs/AndCost.h"
#include "dandan/dandan.h"
#include "dandan/serialization/JsonFactory.h"
#include "nlohmann/json_fwd.hpp"

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{
    using namespace dandan::conditions;
    using namespace dandan::serialization;
    using namespace dandan::costs;

    const auto registered = []
    {
        CostsRegistry::instance().registerType<AndCost>(
            "AndCost",
            [](const dandan::ICost *cost)
            {
                auto json = nlohmann::json::object();
                const auto *and_cost{dynamic_cast<const AndCost *>(cost)};
                const auto &sub_costs = and_cost->getCosts();
                json["sub_costs"] = nlohmann::json::array();
                for (const auto &subcost : sub_costs)
                {
                    json["sub_costs"].push_back(
                        JsonFactory<ICost>::create_json(subcost));
                }
                return json;
            },
            [](const nlohmann::json &json)
            {
                const auto &sub_costs_json = json.at("sub_costs");
                if (!sub_costs_json.is_array() || sub_costs_json.size() != 2)
                {
                    throw std::runtime_error("AndCost JSON must have an array "
                                             "of exactly 2 sub_costs");
                }
                auto first_cost =
                    JsonFactory<ICost>::create_product(sub_costs_json.at(0));
                auto second_cost =
                    JsonFactory<ICost>::create_product(sub_costs_json.at(1));
                return std::make_unique<AndCost>(std::move(first_cost),
                                                 std::move(second_cost));
            });
        return true;
    }();
} // namespace
#endif

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
