#ifndef DANDAN_SCRY_EFFECT_H
#define DANDAN_SCRY_EFFECT_H

#include <utility>

#include "IOneShotEffect.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    /** @brief Reprents the effect of scrying
     * @struct ScryEffect
     *
     * @implements IOneShotEffect
     */
    class ScryEffect final : public IOneShotEffect
    {
    public:
        /** Constructor
         * @param scry_amount the amount of cards to scry
         * @param player the player who will scry
         */
        explicit ScryEffect(int scry_amount, core::PlayerID player,
                            EffectContext context)
            : IOneShotEffect(std::move(context)), m_scry_amount(scry_amount),
              m_player(player)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<ScryEffect>(m_scry_amount, m_player,
                                                getEffectContext());
        }
        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

        [[nodiscard]] int getScryAmount() const
        {
            return m_scry_amount;
        }

    private:
        int m_scry_amount{1};
        core::PlayerID m_player;
    };

    class ScryEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        ScryEffectDefinition() = default;
        explicit ScryEffectDefinition(int scry_amount)
            : m_scry_amount(scry_amount)
        {
        }
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::ExecutionContext exec_ctx,
            EffectContext context) const override
        {
            return std::make_unique<ScryEffect>(
                m_scry_amount, context.player_id.value(), context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<ScryEffectDefinition>(m_scry_amount);
        }

        [[nodiscard]] int getScryAmount() const
        {
            return m_scry_amount;
        }

    private:
        int m_scry_amount{1};
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

    inline const auto registeredScryEffect = []
    {
        OneShotEffectRegistry::instance().registerType<ScryEffectDefinition>(
            "ScryEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *scry_effect =
                    dynamic_cast<const ScryEffectDefinition *>(effect);
                json["scry_amount"] = scry_effect->getScryAmount();

                return json;
            },
            [](const nlohmann::json &data,
               [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                return std::make_unique<ScryEffectDefinition>(
                    data.at("scry_amount").get<int>());
            });
        return true;
    }();
} // namespace
#endif

#endif
