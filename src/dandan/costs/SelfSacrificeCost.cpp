#include "dandan/costs/SelfSacrificeCost.h"

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

    void SelfSacrificeCost::pay(core::ExecutionContext exec_ctx,
                                abilities::AbilityContext context) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        auto &player = game.getPlayer(context.controller_id);
        auto *card = card_registry[context.source_card_id];
        player.sacrificeCard(*card, exec_ctx);
    }

} // namespace dandan::costs
