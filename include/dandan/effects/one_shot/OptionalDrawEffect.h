#ifndef DANDAN_OPTIONALDRAWEFFECT_H
#define DANDAN_OPTIONALDRAWEFFECT_H

#include <utility>

#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    class OptionalDrawEffect : public IOneShotEffect
    {
    public:
        OptionalDrawEffect(int amount, bool each_player, EffectContext context)
            : IOneShotEffect(std::move(context)), m_amount(amount),
              m_each_player(each_player)
        {
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<OptionalDrawEffect>(m_amount, m_each_player,
                                                        getEffectContext());
        }

    private:
        int m_amount;
        bool m_each_player{false};
    };

    class OptionalDrawEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::ExecutionContext exec_ctx,
            [[maybe_unused]] EffectContext context) const override
        {
            return std::make_unique<OptionalDrawEffect>(m_amount, m_each_player,
                                                        context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<OptionalDrawEffectDefinition>(
                m_amount, m_each_player);
        }

        OptionalDrawEffectDefinition(int amount, bool each_player)
            : m_amount(amount), m_each_player(each_player)
        {
        }

        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

        [[nodiscard]] bool isEachPlayer() const
        {
            return m_each_player;
        }

    private:
        int m_amount;
        bool m_each_player{false};
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

    inline const auto registeredOptionalDrawEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<OptionalDrawEffectDefinition>(
                "OptionalDrawEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *optionalDrawEffect =
                        dynamic_cast<const OptionalDrawEffectDefinition *>(
                            effect);
                    json["amount"] = optionalDrawEffect->getAmount();
                    json["each_player"] = optionalDrawEffect->isEachPlayer();

                    return json;
                },
                [](const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<OptionalDrawEffectDefinition>(
                        data.at("amount").get<int>(),
                        data.at("each_player").get<bool>());
                });
        return true;
    }();
} // namespace
#endif

#endif
