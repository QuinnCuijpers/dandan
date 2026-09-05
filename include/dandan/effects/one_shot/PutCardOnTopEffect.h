#ifndef DANDAN_PUTCARDONTOPEFFECT_H
#define DANDAN_PUTCARDONTOPEFFECT_H

#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    /** @brief A one-shot effect that puts a card on top of the deck from the
     * hand.
     * @class PutCardOnTopEffect
     * @implements IOneShotEffect
     */
    class PutCardOnTopEffect : public IOneShotEffect
    {
    public:
        /** @brief Create a PutCardOnTopEffect.
         * @param amount The number of cards to put on top.
         * @param playerID The ID of the player who will use this effect.
         */
        PutCardOnTopEffect(int amount, core::PlayerID playerID,
                           EffectContext context)
            : IOneShotEffect(std::move(context)), m_amount(amount),
              m_playerID(playerID)
        {
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::string display() const override;

        /** @brief Get the amount of cards to put on top.
         * @return The number of cards to put on top.
         */
        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

    private:
        int m_amount{};
        core::PlayerID m_playerID;
    };

    class PutCardOnTopEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        /** @brief Create a PutCardOnTopEffect.
         * @param amount The number of cards to put on top.
         */
        explicit PutCardOnTopEffectDefinition(int amount) : m_amount(amount)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::ExecutionContext exec_ctx,
            EffectContext context) const override
        {
            return std::make_unique<PutCardOnTopEffect>(
                m_amount, context.player_id.value(), context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<PutCardOnTopEffectDefinition>(m_amount);
        }

        // [[nodiscard]] std::string display() const override;

        /** @brief Get the amount of cards to put on top.
         * @return The number of cards to put on top.
         */
        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

    private:
        int m_amount{};
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

    inline const auto registeredPutCardOnTopEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<PutCardOnTopEffectDefinition>(
                "PutCardOnTopEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *put_effect =
                        dynamic_cast<const PutCardOnTopEffectDefinition *>(
                            effect);
                    json["amount"] = put_effect->getAmount();

                    return json;
                },
                [](const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<PutCardOnTopEffectDefinition>(
                        data.at("amount").get<int>());
                });
        return true;
    }();
} // namespace
#endif

#endif
