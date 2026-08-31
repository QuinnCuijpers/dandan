#ifndef DANDAN_MILL_EFFECT_H
#define DANDAN_MILL_EFFECT_H

#include "dandan/core/Card.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    class MillEffect : public IOneShotEffect
    {
    public:
        MillEffect(int amount, core::PlayerID player_id, EffectContext context)
            : IOneShotEffect(std::move(context)), m_amount(amount),
              m_player_id(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<MillEffect>(m_amount, m_player_id,
                                                getEffectContext());
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        int m_amount;
        core::PlayerID m_player_id;
    };

    class MillEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        MillEffectDefinition(int amount,
                             core::TargetRequirement target_requirement)
            : m_amount(amount),
              m_target_requirement(std::move(target_requirement))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            const core::ExecutionContext exec_ctx,
            [[maybe_unused]] EffectContext context) const override
        {
            auto &card_registry{exec_ctx.cards.get()};
            const auto *card{card_registry[context.card_id.value()]};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            auto player_choice{std::get<core::PlayerID>(choice)};
            return std::make_unique<MillEffect>(m_amount, player_choice,
                                                context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<MillEffectDefinition>(m_amount,
                                                          m_target_requirement);
        }

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override
        {
            return &m_target_requirement;
        }

    private:
        int m_amount;
        core::TargetRequirement m_target_requirement;
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

    inline const auto registeredMillEffect = []
    {
        OneShotEffectRegistry::instance().registerType<MillEffectDefinition>(
            "MillEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *mill =
                    dynamic_cast<const MillEffectDefinition *>(effect);
                json["amount"] = mill->getAmount();
                return json;
            },
            [](const nlohmann::json &data,
               const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                return std::make_unique<MillEffectDefinition>(
                    data.at("amount").get<int>(),
                    dandan::core::TargetRequirement{target_specs});
            });
        return true;
    }();
} // namespace
#endif

#endif
