#ifndef DANDAN_BLOCKPREVENTIONEFFECT_H
#define DANDAN_BLOCKPREVENTIONEFFECT_H

#include "dandan/effects/continuous/prevention/IPreventionEffect.h"
#include <memory>
namespace dandan::effects
{
    class BlockPreventionEffect : public IPreventionEffect
    {

    public:
        explicit BlockPreventionEffect(
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
            return std::make_unique<BlockPreventionEffect>(cloneCondition());
        }
    };
} // namespace dandan::effects


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{
    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::conditions;

    inline const auto registeredBlockPreventionEffect = []
    {
        ContinuousEffectRegistry::instance()
            .registerType<BlockPreventionEffect>(
                "BlockPreventionEffect",
                [](const dandan::effects::IContinuousEffect *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *block{
                        dynamic_cast<const BlockPreventionEffect *>(effect)};
                    json["condition"] = JsonFactory<ICondition>::create_json(
                        block->getCondition());
                    return json;
                },
                [](const nlohmann::json &json)
                {
                    auto condition = JsonFactory<ICondition>::create_product(
                        json.at("condition"));
                    return std::make_unique<BlockPreventionEffect>(
                        std::move(condition));
                });
        return true;
    }();
} // namespace
#endif

#endif
