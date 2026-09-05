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
    class ChooseCardNameAndMillEffect : public IOneShotEffect
    {

    public:
        ChooseCardNameAndMillEffect(int amount, core::CardID card_id,
                                    core::Target target,
                                    EffectContext effect_context)
            : IOneShotEffect(std::move(effect_context)), m_amount(amount),
              m_source(card_id), m_target(std::move(target))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<ChooseCardNameAndMillEffect>(
                m_amount, m_source, m_target, getEffectContext());
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        int m_amount;
        core::CardID m_source;
        core::Target m_target;
    };

    class ChooseCardNameAndMillEffectDefinition
        : public IOneShotEffectDefinition
    {

    public:
        explicit ChooseCardNameAndMillEffectDefinition(
            core::TargetRequirement target_reqs)
            : m_target_requirements(std::move(target_reqs))
        {
        }
        ChooseCardNameAndMillEffectDefinition(
            int amount, core::TargetRequirement target_reqs)
            : m_amount(amount), m_target_requirements(std::move(target_reqs))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::ExecutionContext exec_ctx,
            [[maybe_unused]] EffectContext context) const override
        {
            const auto card_registry{exec_ctx.cards.get()};
            const auto *source_card{card_registry[context.card_id.value()]};

            auto choices{source_card->getTargetChoices(*this)};
            auto choice{choices.at(0)};

            return std::make_unique<ChooseCardNameAndMillEffect>(
                m_amount, source_card->getID(), choice, context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<ChooseCardNameAndMillEffectDefinition>(
                m_amount, m_target_requirements);
        }

        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override
        {
            return &m_target_requirements;
        }

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
