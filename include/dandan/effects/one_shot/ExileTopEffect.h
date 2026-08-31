#ifndef DANDAN_EXILETOPEFFECT_H
#define DANDAN_EXILETOPEFFECT_H

#include <utility>

#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    class ExileTopEffect : public IOneShotEffect
    {
    public:
        ExileTopEffect(int amount, core::PlayerID player, EffectContext context)
            : IOneShotEffect(std::move(context)), m_amount(amount),
              m_player(player)
        {
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<ExileTopEffect>(m_amount, m_player,
                                                    getEffectContext());
        }

    private:
        int m_amount;
        core::PlayerID m_player;
    };

    class ExileTopEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::ExecutionContext exec_ctx,
            EffectContext context) const override
        {
            return std::make_unique<ExileTopEffect>(
                m_amount, context.player_id.value(), context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<ExileTopEffectDefinition>(m_amount);
        }

        explicit ExileTopEffectDefinition(int amount) : m_amount(amount)
        {
        }

        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

    private:
        int m_amount;
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

    inline const auto registeredExileTopEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<ExileTopEffectDefinition>(
                "ExileTopEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *exile =
                        dynamic_cast<const ExileTopEffectDefinition *>(effect);
                    json["amount"] = exile->getAmount();
                    return json;
                },
                [](const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<ExileTopEffectDefinition>(
                        data.at("amount").get<int>());
                });
        return true;
    }();
} // namespace
#endif

#endif
