#ifndef DANDAN_ATTACKPREVENTIONEFFECT_H
#define DANDAN_ATTACKPREVENTIONEFFECT_H

#include "IPreventionEffect.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/effects/EffectContext.h"
#include <memory>
#include <optional>

namespace dandan::effects
{
    /** @brief A prevention effect that prevents attacking under a provided
     * condition.
     * @class AttackPreventionEffect
     *
     * @implements IPreventionEffect
     */
    class AttackPreventionEffect : public IPreventionEffect
    {
    public:
        /** Constructs a new attack prevention effect with the given condition.
         * @param condition The condition under which to prevent attacking.
         */
        explicit AttackPreventionEffect(
            std::unique_ptr<conditions::ICondition> condition)
            : IPreventionEffect(std::move(condition))
        {
        }

        [[nodiscard]] bool prevents(const core::IAction &action,
                                    core::ExecutionContext exec_ctx,
                                    std::optional<effects::EffectContext>
                                        context = std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<IPreventionEffect> clone() const override
        {
            return std::make_unique<AttackPreventionEffect>(cloneCondition());
        }
    };

} // namespace dandan::effects


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{
    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::conditions;

    inline const auto registeredAttackPreventionEffect = []
    {
        ContinuousEffectRegistry::instance()
            .registerType<AttackPreventionEffect>(
                "AttackPreventionEffect",
                [](const dandan::effects::IContinuousEffect *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *attack{
                        dynamic_cast<const AttackPreventionEffect *>(effect)};
                    json["condition"] = JsonFactory<ICondition>::create_json(
                        attack->getCondition());
                    return json;
                },
                [](const nlohmann::json &json)
                {
                    auto condition = JsonFactory<ICondition>::create_product(
                        json.at("condition"));
                    return std::make_unique<AttackPreventionEffect>(
                        std::move(condition));
                });
        return true;
    }();
} // namespace
#endif

#endif // DANDAN_ATTACKPREVENTIONEFFECT_H
