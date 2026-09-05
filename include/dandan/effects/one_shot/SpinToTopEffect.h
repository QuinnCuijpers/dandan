#ifndef DANDAN_SPINTOTOPEFFECT_H
#define DANDAN_SPINTOTOPEFFECT_H

#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>
#include <variant>

namespace dandan::effects
{
    class SpinToTopEffect : public IOneShotEffect
    {

    public:
        SpinToTopEffect(core::Target target, EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        core::Target m_target;
    };

    class SpinToTopEffectDefinition : public IOneShotEffectDefinition
    {

    public:
        explicit SpinToTopEffectDefinition(core::TargetRequirement target_req)
            : m_target_requirements(std::move(target_req))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            const core::ExecutionContext exec_ctx,
            EffectContext context) const override
        {
            auto &card_registry{exec_ctx.cards.get()};
            const auto *card{card_registry[context.card_id.value()]};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            return std::make_unique<SpinToTopEffect>(choice, context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<SpinToTopEffectDefinition>(
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

    inline const auto registeredSpinToTopEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<SpinToTopEffectDefinition>(
                "SpinToTopEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<SpinToTopEffectDefinition>(
                        TargetRequirement{target_specs});
                });
        return true;
    }();
} // namespace
#endif

#endif
