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

    void SelfSacrificeCost::pay(core::Game &game,
                                abilities::AbilityContext context) const
    {
        [[maybe_unused]] auto &player = game.getPlayer(context.controller_id);
        auto *card = game.getCardByID(context.source_card_id);
        player.sacrificeCard(*card, game);
    }

} // namespace dandan::costs
