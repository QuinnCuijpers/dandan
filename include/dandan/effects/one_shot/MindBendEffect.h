#ifndef DANDAN_MINDBENDEFFECT_H
#define DANDAN_MINDBENDEFFECT_H

#include <utility>

#include "dandan/core/Card.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/core/TextReplacement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    class MindBendEffect : public IOneShotEffect
    {

    public:
        explicit MindBendEffect(core::Target target, EffectContext context)
            : IOneShotEffect(std::move(context)), m_target(std::move(target))
        {
        }

        // NOLINTBEGIN(bugprone-easily-swappable-parameters)
        MindBendEffect(core::Target target, core::ReplacementType to_replace,
                       core::ReplacementType replace_with,
                       EffectContext context)
            : IOneShotEffect(std::move(context)), m_target(std::move(target)),
              m_to_replace(to_replace), m_replace_with(replace_with)
        {
        }
        // NOLINTEND(bugprone-easily-swappable-parameters)

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<MindBendEffect>(m_target,
                                                    getEffectContext());
        }

        [[nodiscard]] std::string display() const override
        {
            return "Change the text of target permanent by replacing all "
                   "instances of one color word with another or one basic land "
                   "type with another.";
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        core::Target m_target;
        std::optional<core::ReplacementType> m_to_replace;
        std::optional<core::ReplacementType> m_replace_with;
    };

    class MindBendEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        explicit MindBendEffectDefinition(
            core::TargetRequirement target_requirements)
            : m_target_requirements(std::move(target_requirements))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::ExecutionContext exec_ctx,
            [[maybe_unused]] EffectContext context) const override
        {
            auto &card_registry{exec_ctx.cards.get()};
            const auto *card{card_registry[context.card_id.value()]};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            context.expires = expires();
            return std::make_unique<MindBendEffect>(choice, context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<MindBendEffectDefinition>(
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

    inline const auto registeredMindBendEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<MindBendEffectDefinition>(
                "MindBendEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   const std::vector<TargetSpec> &target_specs,
                   ExpireTime expiry)
                {
                    auto effect{std::make_unique<MindBendEffectDefinition>(
                        TargetRequirement{target_specs})};
                    effect->addExpireTime(expiry);
                    return effect;
                });
        return true;
    }();
} // namespace
#endif

#endif
