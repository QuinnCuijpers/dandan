#ifndef DANDAN_MANACOST_H
#define DANDAN_MANACOST_H

#include "ICost.h"
#include "dandan/core/Game.h"
#include "dandan/mana/ManaPrice.h"

namespace dandan::costs
{
    /** @brief A cost that requires a specific amount of mana to be paid.
     * @class ManaCost
     *
     * @implements ICost
     */
    class ManaCost : public ICost
    {
    public:
        /** Constructs a ManaCost with a specific amount of mana.
         * @param mana The mana requirement for the cost.
         */
        explicit ManaCost(mana::ManaPrice price);

        [[nodiscard]] std::string display(
            [[maybe_unused]] bool isFinal = true) const override;

        /** Gets the mana requirement.
         * @return A pointer to the mana requirement.
         */
        [[nodiscard]] const mana::ManaPrice &getMana() const;

        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override;

        void pay(core::ExecutionContext exec_ctx,
                 abilities::AbilityContext context) const override;

    private:
        mana::ManaPrice m_mana;
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
    using namespace dandan::mana;

    inline const auto registeredManaCost = []
    {
        CostsRegistry::instance().registerType<ManaCost>(
            "ManaCost",
            [](const ICost *cost)
            {
                auto json = nlohmann::json::object();
                const auto *mana_cost{dynamic_cast<const ManaCost *>(cost)};
                auto mana = mana_cost->getMana();
                json["mana"] = JsonFactory<ManaPrice>::create_json(&mana);
                return json;
            },
            [](const nlohmann::json &json)
            {
                const auto &mana_json = json.at("mana");
                auto mana = JsonFactory<ManaPrice>::create_product(mana_json);
                return std::make_unique<ManaCost>(std::move(mana));
            });
        return true;
    }();
} // namespace
#endif

#endif
