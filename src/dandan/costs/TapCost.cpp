#include "dandan/costs/TapCost.h"

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

namespace dandan::costs
{
    std::string TapCost::display(bool isFinal) const
    {
        if (isFinal)
        {
            return "[T]: ";
        }
        return "[T]";
    }

    [[nodiscard]] bool TapCost::canPay(
        const core::Card &source,
        [[maybe_unused]] const core::Player &player) const
    {
        return !source.getTapped() &&
               source.getZone() == core::Zone::BATTLEFIELD;
    }

    void TapCost::pay(core::ExecutionContext exec_ctx,
                      abilities::AbilityContext context) const
    {
        const auto &card_registry{exec_ctx.cards.get()};

        auto *card = card_registry[context.source_card_id];
        card->setTapped(true);
    }

} // namespace dandan::costs
