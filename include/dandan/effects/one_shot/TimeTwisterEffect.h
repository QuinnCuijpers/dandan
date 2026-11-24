#ifndef DANDAN_TIMETWISTEREFFECT_H
#define DANDAN_TIMETWISTEREFFECT_H

#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    /** @brief A one-shot effect that moves all hand and graveyard cards into
     * the library and shuffles it.
     * @class TimeTwisterEffect
     * @implements IOneShotEffect
     */
    class TimeTwisterEffect : public IOneShotEffect
    {
    public:
        /** @brief Creates a Time Twister effect.
         * @param context Effect execution context.
         */
        explicit TimeTwisterEffect(EffectContext context);

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;
    };

    /** @brief Effect definition for the Time Twister effect.
     * @class TimeTwisterEffectDefinition
     * @implements IOneShotEffectDefinition
     */
    class TimeTwisterEffectDefinition : public IOneShotEffectDefinition
    {
        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            [[maybe_unused]] EffectContext context) const override;
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

    inline const auto registeredTimeTwisterEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<TimeTwisterEffectDefinition>(
                "TimeTwisterEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                { return std::make_unique<TimeTwisterEffectDefinition>(); });
        return true;
    }();
} // namespace
#endif

#endif
