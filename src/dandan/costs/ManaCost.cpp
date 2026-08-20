#include "dandan/costs/ManaCost.h"
#include "dandan/mana/Manapool.h"
#include "dandan/serialization/JsonFactory.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{
    using namespace dandan::conditions;
    using namespace dandan::serialization;
    using namespace dandan::costs;
    using namespace dandan::mana;

    const auto registered = []
    {
        CostsRegistry::instance().registerType<ManaCost>(
            "ManaCost",
            [](const ICost *cost)
            {
                auto json = nlohmann::json::object();
                const auto *mana_cost{dynamic_cast<const ManaCost *>(cost)};
                json["mana"] =
                    JsonFactory<Manapool>::create_json(mana_cost->getMana());
                return json;
            },
            [](const nlohmann::json &json)
            {
                const auto &mana_json = json.at("mana");
                auto mana = JsonFactory<Manapool>::create_product(mana_json);
                return std::make_unique<ManaCost>(std::move(mana));
            });
        return true;
    }();
} // namespace
#endif

namespace dandan::costs
{

    ManaCost::ManaCost(mana::ManaPrice price) : m_mana{std::move(price)} {};

    std::string ManaCost::display([[maybe_unused]] bool isFinal) const
    {
        std::string res{};
        auto generic_str = m_mana.generic() != 0
                               ? "(" + std::to_string(m_mana.generic()) + ")"
                               : "";
        res += generic_str;
        res += mana::ManaBag::ManaToSymbols(m_mana.specific());
        return res;
    }

    [[nodiscard]] mana::ManaPrice ManaCost::getMana() const
    {
        return m_mana;
    }

    [[nodiscard]] bool ManaCost::canPay(
        [[maybe_unused]] const core::Card &source,
        const core::Player &player) const
    {
        return player.manaPool().canPay(m_mana);
    }

    void ManaCost::pay([[maybe_unused]] core::Game &game,
                       [[maybe_unused]] abilities::AbilityContext context) const
    {
        auto &player = game.getPlayer(context.controller_id);
        player.manaPool().pay(m_mana);
    }

} // namespace dandan::costs
