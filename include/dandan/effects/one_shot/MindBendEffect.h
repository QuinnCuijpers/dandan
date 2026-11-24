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
    /** @brief Effect that changes text on a target permanent.
     * @class MindBendEffect
     *
     * @implements IOneShotEffect
     */
    class MindBendEffect : public IOneShotEffect
    {

    public:
        /** @brief Constructs a mind bend effect that prompts for replacements.
         * @param target Permanent whose text is changed.
         * @param context Effect execution context.
         */
        explicit MindBendEffect(core::Target target, EffectContext context);

        /** @brief Constructs a mind bend effect with fixed replacements.
         * @param target Permanent whose text is changed.
         * @param to_replace Text to replace.
         * @param replace_with Replacement text.
         * @param context Effect execution context.
         */
        MindBendEffect(core::Target target, core::ReplacementType to_replace,
                       core::ReplacementType replace_with,
                       EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        core::Target m_target;
        std::optional<core::ReplacementType> m_to_replace;
        std::optional<core::ReplacementType> m_replace_with;
    };

    /** @brief Definition of an effect that changes text on a permanent.
     * @class MindBendEffectDefinition
     *
     * @implements IOneShotEffectDefinition
     */
    class MindBendEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        /** @brief Constructs a mind bend effect definition.
         * @param target_requirements Requirements for the target permanent.
         */
        explicit MindBendEffectDefinition(
            core::TargetRequirement target_requirements);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            [[maybe_unused]] EffectContext context) const override;

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
                        TargetRequirement{target_specs}),};
                    effect->addExpireTime(expiry);
                    return effect;
                });
        return true;
    }();
} // namespace
#endif

#endif
