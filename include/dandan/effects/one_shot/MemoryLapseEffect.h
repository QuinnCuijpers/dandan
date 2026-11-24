#ifndef DANDAN_MemoryLapseEFFECT_H
#define DANDAN_MemoryLapseEFFECT_H

#include "dandan/core/Card.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/core/Zone.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    /** @brief Counterspell effect that returns a countered card to a zone.
     * @class MemoryLapseEffect
     *
     * @implements IOneShotEffect
     */
    class MemoryLapseEffect : public IOneShotEffect
    {

    public:
        /** @brief Constructs a memory lapse effect.
         * @param target Card to counter.
         * @param context Effect execution context.
         * @param target_zone Zone to move the card to when countered.
         */
        explicit MemoryLapseEffect(
            core::Target target, EffectContext context,
            core::Zone target_zone = core::Zone::LIBRARY);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        core::Target m_target;
        core::Zone m_target_zone{core::Zone::LIBRARY};
    };

    /** @brief Definition of a memory lapse effect.
     * @class MemoryLapseEffectDefinition
     *
     * @implements IOneShotEffectDefinition
     */
    class MemoryLapseEffectDefinition : public IOneShotEffectDefinition
    {

    public:
        /** @brief Constructs a memory lapse effect definition.
         * @param target_requirements Requirements for the card to counter.
         */
        explicit MemoryLapseEffectDefinition(
            core::TargetRequirement target_requirements);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            core::ExecutionContext exec_ctx,
            EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override;

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override;

    private:
        core::TargetRequirement m_target_requirements;
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

    inline const auto registeredMemoryLapseEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<MemoryLapseEffectDefinition>(
                "MemoryLapseEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<MemoryLapseEffectDefinition>(
                        TargetRequirement{target_specs});
                });
        return true;
    }();
} // namespace
#endif

#endif
