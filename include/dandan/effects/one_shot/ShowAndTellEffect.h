#ifndef DANDAN_SHOWANDTELLEFFECT_H
#define DANDAN_SHOWANDTELLEFFECT_H

#include "dandan/core/PlayerID.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    class ShowAndTellEffect : public IOneShotEffect
    {

    public:
        ShowAndTellEffect(core::PlayerID player_id, EffectContext context)
            : IOneShotEffect(std::move(context)), m_player(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<ShowAndTellEffect>(m_player,
                                                       getEffectContext());
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        const std::array<core::Type, 4> m_types{
            core::Type::Artifact, core::Type::Creature, core::Type::Enchantment,
            core::Type::Land};
        core::PlayerID m_player;
    };

    class ShowAndTellEffectDefinition : public IOneShotEffectDefinition
    {

    public:
        explicit ShowAndTellEffectDefinition(
            core::TargetRequirement target_requirement)
            : m_target_requirements(std::move(target_requirement))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::ExecutionContext exec_ctx,
            EffectContext context) const override
        {
            auto player_id{context.player_id.value()};
            return std::make_unique<ShowAndTellEffect>(player_id, context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<ShowAndTellEffectDefinition>(
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

    inline const auto registeredShowAndTellEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<ShowAndTellEffectDefinition>(
                "ShowAndTellEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<ShowAndTellEffectDefinition>(
                        TargetRequirement{target_specs});
                });
        return true;
    }();
} // namespace
#endif

#endif
