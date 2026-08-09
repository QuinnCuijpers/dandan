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

    ManaCost::ManaCost(std::unique_ptr<mana::Manapool> mana)
        : m_mana{std::move(mana)} {};

    std::string ManaCost::display([[maybe_unused]] bool isFinal) const
    {
        std::string res{};
        res += mana::ManaToSymbols(m_mana->getMana());
        return res;
    }

    [[nodiscard]] mana::Manapool *ManaCost::getMana() const
    {
        return m_mana.get();
    }

    [[nodiscard]] bool ManaCost::canPay(
        [[maybe_unused]] const core::Card &source,
        const core::Player &player) const
    {
        return player.manaPool().canPay(*m_mana);
    }

    void ManaCost::pay([[maybe_unused]] core::Game &game,
                       [[maybe_unused]] abilities::AbilityContext context) const
    {
        auto &player = game.getPlayer(context.controller_id);
        player.manaPool().pay(*m_mana);
    }

} // namespace dandan::costs
