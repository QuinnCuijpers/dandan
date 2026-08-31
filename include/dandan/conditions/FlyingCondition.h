#ifndef DANDAN_FLYINGCONDITION_H
#define DANDAN_FLYINGCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include <memory>
namespace dandan::conditions
{
    class FlyingCondition : public ICondition
    {

    public:
        [[nodiscard]] bool isSatisfied(
            core::ExecutionContext exec_ctx,
            std::optional<effects::EffectContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override;
    };
} // namespace dandan::conditions


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{
    using namespace dandan::conditions;
    using namespace dandan::serialization;

    inline const auto registeredFlyingCondition = []
    {
        ConditionRegistry::instance().registerType<FlyingCondition>(
            "FlyingCondition",
            []([[maybe_unused]] const ICondition *condition)
            {
                auto json = nlohmann::json::object();
                return json;
            },
            []([[maybe_unused]] const nlohmann::json &json)
            { return std::make_unique<FlyingCondition>(); });
        return true;
    }();
} // namespace
#endif

#endif
