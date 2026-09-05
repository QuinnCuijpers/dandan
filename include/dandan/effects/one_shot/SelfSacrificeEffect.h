#ifndef DANDAN_SELFSACRIFICEEFFECT_H
#define DANDAN_SELFSACRIFICEEFFECT_H

#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

// should take a card as member variable, but cant rn due to serialization
namespace dandan::effects
{
    /**
     * @brief Represents an effect that sacrifices the underlying card
     *@class SelfSacrificeEffect
     *
     *@implements IOneShotEffect
     */
    class SelfSacrificeEffect : public IOneShotEffect
    {
    public:
        explicit SelfSacrificeEffect(core::CardID card_id,
                                     EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            [[maybe_unused]] core::ExecutionContext exec_ctx) const override;

    private:
        core::CardID m_card_id;
    };

    class SelfSacrificeEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::ExecutionContext exec_ctx,
            [[maybe_unused]] EffectContext context) const override
        {
            return std::make_unique<SelfSacrificeEffect>(
                context.card_id.value(), context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<SelfSacrificeEffectDefinition>();
        }
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

    inline const auto registeredSelfSacrificeEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<SelfSacrificeEffectDefinition>(
                "SelfSacrificeEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                { return std::make_unique<SelfSacrificeEffectDefinition>(); });
        return true;
    }();
} // namespace
#endif

#endif
