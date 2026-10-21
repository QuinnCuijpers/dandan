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
        [[nodiscard]] Keyword keyword() const override
        {
            return Keyword::Flashback;
        }

        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            [[maybe_unused]] AbilityContext context) const override
        {
            return nullptr;
        }

        explicit FlashbackAbility(mana::ManaPrice cost)
            : m_cost(std::move(cost))
        {
        }

        [[nodiscard]] const mana::ManaPrice &getCost() const
        {
            return m_cost;
        }

        [[nodiscard]] std::unique_ptr<IAbility> clone() const override
        {
            return std::make_unique<FlashbackAbility>(m_cost);
        }

    private:
        mana::ManaPrice m_cost;
    };
} // namespace dandan::abilities

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
#include <utility>

namespace dandan::serialization::registration
{

    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::effects;

    inline const auto registeredFlashbackAbility = []
    {
        AbilityRegistry::instance().registerType<FlashbackAbility>(
            "FlashbackAbility",
            [](const IAbility *ability)
            {
                auto json = nlohmann::json::object();
                const auto *flash_ability{
                    dynamic_cast<const FlashbackAbility *>(ability)};
                json["cost"] = JsonFactory<mana::ManaPrice>::create_json(
                    &flash_ability->getCost());

                return json;
            },
            [](const nlohmann::json &json)
            {
                return std::make_unique<FlashbackAbility>(
                    JsonFactory<mana::ManaPrice>::create_product(json["cost"]));
            });

        return true;
    }();
} // namespace dandan::serialization::registration
#endif

#endif
