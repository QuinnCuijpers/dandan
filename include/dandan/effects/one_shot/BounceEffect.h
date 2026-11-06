
#ifndef DANDAN_BOUNCEEffect_H
#define DANDAN_BOUNCEEffect_H

#include <stdexcept>
#include <utility>

#include "dandan/core/Card.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    class BounceEffect : public IOneShotEffect
    {

    public:
        explicit BounceEffect(core::Target target, EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        core::Target m_target;
    };

    class BounceEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        explicit BounceEffectDefinition(
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
    using namespace dandan::core;

    inline const auto registeredBounceEffect = []
    {
        OneShotEffectRegistry::instance().registerType<BounceEffectDefinition>(
            "BounceEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                const auto json = nlohmann::json::object();
                return json;
            },
            []([[maybe_unused]] const nlohmann::json &data,
               const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                return std::make_unique<BounceEffectDefinition>(
                    TargetRequirement{target_specs});
            });
        return true;
    }();
} // namespace
#endif

#endif
