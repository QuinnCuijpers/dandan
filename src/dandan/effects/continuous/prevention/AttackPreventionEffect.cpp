#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/core/actions/AttackAction.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/continuous/IContinuousEffect.h"
#include "dandan/serialization/JsonFactory.h"
#include <iostream>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{
    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::conditions;

    const auto registered = []
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

namespace dandan::effects
{
    bool AttackPreventionEffect::prevents(
        const core::IAction &action, const core::ExecutionContext exec_ctx,
        std::optional<effects::EffectContext> context) const
    {
        if ([[maybe_unused]] const auto *attack_action =
                dynamic_cast<const core::AttackAction *>(&action))
        {

            std::cout << "Checking attack prevention effect condition\n";
            if (getCondition()->isSatisfied(exec_ctx, context))
            {
                // TODO: give conditions display
                //  std::cout << "Attack prevention with condition "
                //            << typeid(*getCondition()).name()
                //            << " prevents attack action\n";
                return true;
            }
        }
        return false;
    }
} // namespace dandan::effects
