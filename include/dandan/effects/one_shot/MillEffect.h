#ifndef DANDAN_MILL_EFFECT_H
#define DANDAN_MILL_EFFECT_H

#include "dandan/core/Card.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    /** @brief Effect that mills cards from a player's library.
     * @class MillEffect
     *
     * @implements IOneShotEffect
     */
    class MillEffect : public IOneShotEffect
    {
    public:
        /** @brief Constructs a mill effect.
         * @param amount Number of cards to mill.
         * @param player_id Player whose library is milled.
         * @param context Effect execution context.
         */
        MillEffect(int amount, core::PlayerID player_id, EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        int m_amount;
        core::PlayerID m_player_id;
    };

    /** @brief Definition of an effect that mills cards from a library.
     * @class MillEffectDefinition
     *
     * @implements IOneShotEffectDefinition
     */
    class MillEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        /** @brief Constructs a mill effect definition.
         * @param amount Number of cards to mill.
         * @param target_requirement Requirement for the player to mill.
         */
        MillEffectDefinition(int amount,
                             core::TargetRequirement target_requirement);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            core::ExecutionContext exec_ctx,
            [[maybe_unused]] EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override;

        [[nodiscard]] std::string display() const override;

        /** @brief Gets the number of cards to mill.
         * @return Number of cards to mill.
         */
        [[nodiscard]] int getAmount() const;

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override;

    private:
        int m_amount;
        core::TargetRequirement m_target_requirement;
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

    inline const auto registeredMillEffect = []
    {
        OneShotEffectRegistry::instance().registerType<MillEffectDefinition>(
            "MillEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *mill =
                    dynamic_cast<const MillEffectDefinition *>(effect);
                json["amount"] = mill->getAmount();
                return json;
            },
            [](const nlohmann::json &data,
               const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                return std::make_unique<MillEffectDefinition>(
                    data.at("amount").get<int>(),
                    dandan::core::TargetRequirement{target_specs});
            });
        return true;
    }();
} // namespace
#endif

#endif
