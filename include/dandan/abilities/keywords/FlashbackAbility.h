#ifndef DANDAN_FLASHBACKABILITY_H
#define DANDAN_FLASHBACKABILITY_H

#include "dandan/abilities/keywords/IKeyWordAbility.h"
#include "dandan/abilities/keywords/Keyword.h"
#include "dandan/mana/ManaPrice.h"

namespace dandan::abilities
{
    class FlashbackAbility final : public IKeyWordAbility
    {
    public:
        [[nodiscard]] Keyword keyword() const override;

        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            [[maybe_unused]] AbilityContext context) const override;

        explicit FlashbackAbility(mana::ManaPrice cost);

        [[nodiscard]] const mana::ManaPrice &getCost() const;

        [[nodiscard]] std::unique_ptr<IAbility> clone() const override;

    private:
        mana::ManaPrice m_cost;
    };
} // namespace dandan::abilities

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization::registration
{

    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::effects;

    static const auto registeredFlashbackAbility = []() noexcept
    {
        AbilityRegistry::instance().registerType<FlashbackAbility>(
            "FlashbackAbility",
            [](const IAbility *ability)
            {
                const auto *flash_ability{
                    dynamic_cast<const FlashbackAbility *>(ability),
                };
                auto json = nlohmann::json{
                    {
                        "cost",
                        JsonFactory<mana::ManaPrice>::create_json(
                            &flash_ability->getCost()),
                    },
                };

                return json;
            },
            [](const nlohmann::json &json)
            {
                return std::make_unique<FlashbackAbility>(
                    JsonFactory<mana::ManaPrice>::create_product(
                        json.at("cost")));
            });

        return true;
    }();
} // namespace dandan::serialization::registration
#endif

#endif
