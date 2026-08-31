#ifndef DANDAN_TAPCOST_H
#define DANDAN_TAPCOST_H

#include "dandan/costs/ICost.h"

namespace dandan::costs
{

    /**
     * @brief A cost that requires the player to tap the source card.
     * @class TapCost
     *
     * @implements ICost
     */
    class TapCost : public ICost
    {
    public:
        TapCost() = default;

        [[nodiscard]] std::string display(bool isFinal = true) const override;

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

    inline const auto registeredTapCost = []
    {
        CostsRegistry::instance().registerType<TapCost>(
            "TapCost",
            []([[maybe_unused]] const ICost *cost)
            {
                auto json = nlohmann::json::object();
                return json;
            },
            []([[maybe_unused]] const nlohmann::json &json)
            { return std::make_unique<TapCost>(); });
        return true;
    }();
} // namespace
#endif

#endif
