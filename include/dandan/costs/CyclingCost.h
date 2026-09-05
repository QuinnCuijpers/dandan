#ifndef DANDAN_CYCLING_H
#define DANDAN_CYCLING_H

#include "ICost.h"
#include "dandan/core/Game.h"
#include <memory>

namespace dandan::costs
{
    /** @brief The cost representing the cost part of the cycling ability. It is
     * a decorator around an inner cost.
     * @class CyclingCost
     *
     * @implements ICost
     */
    class CyclingCost final : public ICost
    {
    public:
        /** Constructs a CyclingCost with an inner cost.
         * @param inner_cost The inner cost to decorate.
         */
        explicit CyclingCost(std::unique_ptr<ICost> inner_cost);

        [[nodiscard]] std::string display(
            [[maybe_unused]] bool isFinal = true) const override;

        /** Gets the inner cost.
         * @return A pointer to the inner cost.
         */
        [[nodiscard]] const ICost *getInnerCost() const;

        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override;

        void pay(core::ExecutionContext exec_ctx,
                 abilities::AbilityContext context) const override;

    private:
        std::unique_ptr<ICost> m_inner_cost;
    };
} // namespace dandan::costs


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{
    using namespace dandan::serialization;
    using namespace dandan::costs;

    inline const auto registeredCyclingCost = []
    {
        CostsRegistry::instance().registerType<CyclingCost>(
            "CyclingCost",
            [](const ICost *cost)
            {
                auto json = nlohmann::json::object();
                const auto *cycle_cost{dynamic_cast<const CyclingCost *>(cost)};
                const auto *inner_cost = cycle_cost->getInnerCost();
                json["inner_cost"] =
                    JsonFactory<ICost>::create_json(inner_cost);
                return json;
            },
            [](const nlohmann::json &json)
            {
                const auto &generic_cost_json = json.at("inner_cost");
                auto generic_cost =
                    JsonFactory<ICost>::create_product(generic_cost_json);
                return std::make_unique<CyclingCost>(std::move(generic_cost));
            });
        return true;
    }();
} // namespace
#endif

#endif
