#ifndef DANDAN_ANDCOST_H
#define DANDAN_ANDCOST_H

#include "dandan/costs/ICost.h"
#include <memory>
#include <vector>

namespace dandan::costs
{
    /** @brief A composite cost that requires its left and right sub-costs to be
     * satisfied.
     * @class AndCost
     *
     * @implements ICost
     */
    class AndCost : public ICost
    {
    public:
        /** Constructs an AndCost with two sub-costs.
         * @param first The first sub-cost.
         * @param second The second sub-cost.
         */
        AndCost(std::unique_ptr<ICost> first, std::unique_ptr<ICost> second);

        [[nodiscard]] std::string display(
            [[maybe_unused]] bool isFinal = true) const override;

        /** Gets the sub-costs.
         * @return A vector of the sub-costs.
         */
        [[nodiscard]] std::vector<ICost *> getCosts() const;

        void pay(core::ExecutionContext exec_ctx,
                 abilities::AbilityContext context) const override;

        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override;

    private:
        std::unique_ptr<ICost> m_first;
        std::unique_ptr<ICost> m_second;
    };
} // namespace dandan::costs

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{
    using namespace dandan::conditions;
    using namespace dandan::serialization;
    using namespace dandan::costs;

    inline const auto registeredAndCost = []
    {
        CostsRegistry::instance().registerType<AndCost>(
            "AndCost",
            [](const ICost *cost)
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
} // namespace dandan::serialization::registration
#endif

#endif // DANDAN_ANDCOST_H
