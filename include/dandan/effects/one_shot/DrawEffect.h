#ifndef DANDAN_DRAWEFFECT_H
#define DANDAN_DRAWEFFECT_H

#include <utility>

#include "dandan/core/ExecutionContext.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/INumber.h"

namespace dandan::effects
{
    class DrawEffect : public IOneShotEffect
    {
    public:
        DrawEffect(std::unique_ptr<numbers::INumber> amount,
                   EffectContext context)
            : IOneShotEffect(std::move(context)), m_amount(std::move(amount))
        {
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<DrawEffect>(m_amount->clone(),
                                                getEffectContext());
        }

    private:
        std::unique_ptr<numbers::INumber> m_amount;
    };

    class DrawEffectDefinition final : public IOneShotEffectDefinition
    {
    public:
        DrawEffectDefinition() = default;
        /** Constructor
         * @param amount the amount of cards this effect would draw
         */
        explicit DrawEffectDefinition(int amount)
            : m_amount(std::make_unique<numbers::ExactNumber>(amount))
        {
        }

        explicit DrawEffectDefinition(std::unique_ptr<numbers::INumber> amount)
            : m_amount(std::move(amount))
        {
        }

        [[nodiscard]] const std::unique_ptr<numbers::INumber> &getNumber() const
        {
            return m_amount;
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            EffectContext context) const override
        {
            return std::make_unique<DrawEffect>(m_amount->clone(), context);
        }

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<DrawEffectDefinition>(m_amount->clone());
        }

    private:
        std::unique_ptr<numbers::INumber> m_amount{
            std::make_unique<numbers::ExactNumber>(1)};
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

    inline const auto registeredDrawEffect = []
    {
        OneShotEffectRegistry::instance().registerType<DrawEffectDefinition>(
            "DrawEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *draw_effect =
                    dynamic_cast<const DrawEffectDefinition *>(effect);
                auto *number{draw_effect->getNumber().get()};
                if (const auto *exactNumber =
                        dynamic_cast<const ExactNumber *>(number))
                {
                    json["amount"] = exactNumber->getValue();
                }
                else
                {
                    json["amount"] = JsonFactory<INumber>::create_json(number);
                }
                return json;
            },
            [](const nlohmann::json &data,
               [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                const auto &amount_json = data.at("amount");
                if (amount_json.is_number_integer())
                {
                    return std::make_unique<DrawEffectDefinition>(
                        amount_json.get<int>());
                }
                auto amount = JsonFactory<INumber>::create_product(amount_json);
                return std::make_unique<DrawEffectDefinition>(
                    std::move(amount));
            });
        return true;
    }();
} // namespace
#endif

#endif
