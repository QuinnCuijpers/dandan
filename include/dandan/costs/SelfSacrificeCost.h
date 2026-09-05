#ifndef DANDAN_SELFSACRIFICECOST_H
#define DANDAN_SELFSACRIFICECOST_H

#include "dandan/core/Game.h"
#include "dandan/costs/ICost.h"

namespace dandan::costs
{
    /** @brief A cost that requires the player to sacrifice one of their own
     * cards.
     * @class SelfSacrificeCost
     * @implements ICost
     */
    class SelfSacrificeCost : public ICost
    {
    public:
        SelfSacrificeCost() = default;

        [[nodiscard]] std::string display(
            [[maybe_unused]] bool isFinal = true) const override;

        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override;

        void pay(core::ExecutionContext exec_ctx,
                 abilities::AbilityContext context) const override;
    };
} // namespace dandan::costs


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{
    using namespace dandan::conditions;
    using namespace dandan::serialization;
    using namespace dandan::costs;

    inline const auto registeredSelfSacrificeCost = []
    {
        CostsRegistry::instance().registerType<SelfSacrificeCost>(
            "SelfSacrificeCost",
            []([[maybe_unused]] const ICost *cost)
            {
                auto json = nlohmann::json::object();
                return json;
            },
            []([[maybe_unused]] const nlohmann::json &json)
            { return std::make_unique<SelfSacrificeCost>(); });
        return true;
    }();
} // namespace
#endif

#endif
