#ifndef DANDAN_BOUNCELANDEFFECT_H
#define DANDAN_BOUNCELANDEFFECT_H

#include "IOneShotEffect.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    /** @brief Represents bouncing a land you control back to your hand
     * @class BounceLandEffect
     *
     * @implements IOneShotEffect
     */
    class BounceLandEffect : public IOneShotEffect
    {
    public:
        explicit BounceLandEffect(core::PlayerID player_id,
                                  EffectContext effect_context)
            : IOneShotEffect(std::move(effect_context)), m_player_id(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<BounceLandEffect>(m_player_id,
                                                      getEffectContext());
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        core::PlayerID m_player_id;
    };

    class BounceLandEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<BounceLandEffectDefinition>();
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            EffectContext context) const override;
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
    using namespace dandan::core;

    inline const auto registeredBounceLandEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<BounceLandEffectDefinition>(
                "BounceLandEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    const auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                { return std::make_unique<BounceLandEffectDefinition>(); });
        return true;
    }();
} // namespace
#endif

#endif // DANDAN_BOUNCELANDEFFECT_H
