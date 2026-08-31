#ifndef DANDAN_PEEK_EFFECT_H
#define DANDAN_PEEK_EFFECT_H

#include <utility>

#include "IOneShotEffect.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
namespace dandan::effects
{

    /** @brief Represents the effect of looking at the top few cards of the
     * library
     * @class PeekEffect
     *
     * @implements @IOneShotEffect
     */
    class PeekEffect final : public IOneShotEffect
    {
    public:
        /** Constructor
         *@param peek_amount the amount of cards to peek.
         */
        explicit PeekEffect(int peek_amount, core::PlayerID player_id,
                            EffectContext context)
            : IOneShotEffect(std::move(context)), m_peek_amount(peek_amount),
              m_player_id(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<PeekEffect>(m_peek_amount, m_player_id,
                                                getEffectContext());
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        int m_peek_amount{3};
        core::PlayerID m_player_id;
    };

    class PeekEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        PeekEffectDefinition() = default;
        explicit PeekEffectDefinition(int peek_amount)
            : m_peek_amount(peek_amount)
        {
        }
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::ExecutionContext exex_ctx,
            EffectContext context) const override
        {
            return std::make_unique<PeekEffect>(
                m_peek_amount, context.player_id.value(), context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<PeekEffectDefinition>(m_peek_amount);
        }

        [[nodiscard]] int getPeekAmount() const
        {
            return m_peek_amount;
        }

    private:
        int m_peek_amount{3};
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

    inline const auto registeredPeekEffect = []
    {
        OneShotEffectRegistry::instance().registerType<PeekEffectDefinition>(
            "PeekEffect",
            [](const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *peek_effect =
                    dynamic_cast<const PeekEffectDefinition *>(effect);
                json["peek_amount"] = peek_effect->getPeekAmount();

                return json;
            },
            [](const nlohmann::json &data,
               [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                return std::make_unique<PeekEffectDefinition>(
                    data.at("peek_amount").get<int>());
            });
        return true;
    }();
} // namespace
#endif

#endif
