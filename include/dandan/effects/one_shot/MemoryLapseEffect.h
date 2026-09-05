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
    class MemoryLapseEffect : public IOneShotEffect
    {

    public:
        explicit MemoryLapseEffect(core::Target target, EffectContext context,
                                   core::Zone target_zone = core::Zone::LIBRARY)
            : IOneShotEffect(std::move(context)), m_target(std::move(target)),
              m_target_zone(target_zone)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<MemoryLapseEffect>(m_target,
                                                       getEffectContext());
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        core::Target m_target;
        core::Zone m_target_zone{core::Zone::LIBRARY};
    };

    class MemoryLapseEffectDefinition : public IOneShotEffectDefinition
    {

    public:
        explicit MemoryLapseEffectDefinition(
            core::TargetRequirement target_requirements)
            : m_target_requirements(std::move(target_requirements))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            const core::ExecutionContext exec_ctx,
            EffectContext context) const override
        {
            auto card_registry{exec_ctx.cards.get()};
            const auto *card{card_registry[context.card_id.value()]};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            return std::make_unique<MemoryLapseEffect>(choice, context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<MemoryLapseEffectDefinition>(
                m_target_requirements);
        }

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override
        {
            return &m_target_requirements;
        }

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
