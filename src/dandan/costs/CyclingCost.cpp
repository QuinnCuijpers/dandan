#include "dandan/costs/CyclingCost.h"
#include "dandan/serialization/JsonFactory.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{
    using namespace dandan::serialization;
    using namespace dandan::costs;

    const auto registered = []
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
        const auto &card_registry{exec_ctx.cards.get()};

        m_inner_cost->pay(exec_ctx, context);
        auto player_id{context.controller_id};
        auto &player{game.getPlayer(player_id)};
        auto *card{card_registry[context.source_card_id]};
        player.discardCard(*card, exec_ctx);
    }

} // namespace dandan::costs
