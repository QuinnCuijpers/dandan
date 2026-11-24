#ifndef DANDAN_SCRY_EFFECT_H
#define DANDAN_SCRY_EFFECT_H

#include <utility>

#include "IOneShotEffect.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    /** @brief Represents the effect of scrying cards.
     * @struct ScryEffect
     *
     * @implements IOneShotEffect
     */
    class ScryEffect final : public IOneShotEffect
    {
    public:
        /** @brief Creates a scry effect.
         * @param scry_amount The number of cards to scry.
         * @param player The player who will scry.
         * @param context Effect execution context.
         */
        explicit ScryEffect(int scry_amount, core::PlayerID player,
                            EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;
        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

        /** @brief Gets the number of cards to scry.
         * @return The number of cards to scry.
         */
        [[nodiscard]] int getScryAmount() const;

    private:
        int m_scry_amount{1};
        core::PlayerID m_player;
    };

    /** @brief Effect definition for scrying a configurable number of cards.
     * @class ScryEffectDefinition
     * @implements IOneShotEffectDefinition
     */
    class ScryEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        ScryEffectDefinition() = default;

        /** @brief Creates a scry effect definition.
         * @param scry_amount The number of cards to scry.
         */
        explicit ScryEffectDefinition(int scry_amount);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override;

        /** @brief Gets the number of cards to scry.
         * @return The number of cards to scry.
         */
        [[nodiscard]] int getScryAmount() const;

    private:
        int m_scry_amount{1};
    };
} // namespace dandan::effects


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{

    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::abilities;
    using namespace dandan::core;
    using namespace dandan::numbers;

    inline const auto registeredScryEffect = []
    {
        OneShotEffectRegistry::instance().registerType<ScryEffectDefinition>(
            "ScryEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *scry_effect =
                    dynamic_cast<const ScryEffectDefinition *>(effect);
                json["scry_amount"] = scry_effect->getScryAmount();

                return json;
            },
            [](const nlohmann::json &data,
               [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                return std::make_unique<ScryEffectDefinition>(
                    data.at("scry_amount").get<int>());
            });
        return true;
    }();
} // namespace
#endif

#endif
