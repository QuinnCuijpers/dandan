#ifndef CHOOSECARDNAMEANDMILLEFFECT_H
#define CHOOSECARDNAMEANDMILLEFFECT_H

#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    /** @brief One-shot effect that chooses a card name and mills matching cards.
     * @class ChooseCardNameAndMillEffect
     *
     * @implements IOneShotEffect
     */
    class ChooseCardNameAndMillEffect : public IOneShotEffect
    {

    public:
        /** @brief Constructs a choose-name-and-mill effect.
         * @param amount Number of cards to mill.
         * @param card_id Source card identifier.
         * @param target Target whose library is affected.
         * @param effect_context Effect execution context.
         */
        ChooseCardNameAndMillEffect(int amount, core::CardID card_id,
                                    core::Target target,
                                    EffectContext effect_context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        int m_amount;
        core::CardID m_source;
        core::Target m_target;
    };

    /** @brief Definition for creating choose-name-and-mill effects.
     * @class ChooseCardNameAndMillEffectDefinition
     *
     * @implements IOneShotEffectDefinition
     */
    class ChooseCardNameAndMillEffectDefinition
        : public IOneShotEffectDefinition
    {

    public:
        /** @brief Constructs a definition with default amount.
         * @param target_reqs Target selection requirements.
         */
        explicit ChooseCardNameAndMillEffectDefinition(
            core::TargetRequirement target_reqs);
        /** @brief Constructs a definition with a mill amount.
         * @param amount Number of cards to mill.
         * @param target_reqs Target selection requirements.
         */
        ChooseCardNameAndMillEffectDefinition(
            int amount, core::TargetRequirement target_reqs);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            [[maybe_unused]] EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override;

        /** @brief Gets the configured mill amount.
         * @return Number of cards to mill.
         */
        [[nodiscard]] int getAmount() const;

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override;

    private:
        int m_amount{1};
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

    inline const auto registeredChooseCardNameAndMillEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<ChooseCardNameAndMillEffectDefinition>(
                "ChooseCardNameAndMillEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *choose_name_and_mill = dynamic_cast<
                        const ChooseCardNameAndMillEffectDefinition *>(effect);
                    json["amount"] = choose_name_and_mill->getAmount();
                    return json;
                },
                [](const nlohmann::json &data,
                   const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<
                        ChooseCardNameAndMillEffectDefinition>(
                        data.at("amount").get<int>(),
                        TargetRequirement{target_specs});
                });
        return true;
    }();
} // namespace
#endif

#endif
