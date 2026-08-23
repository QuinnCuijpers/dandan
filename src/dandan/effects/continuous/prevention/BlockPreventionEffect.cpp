#include "dandan/effects/continuous/prevention/BlockPreventionEffect.h"
#include "dandan/core/actions/BlockAction.h"
#include "dandan/effects/EffectContext.h"
#include <iostream>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
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

namespace dandan::effects
{
    bool BlockPreventionEffect::prevents(
        const core::IAction &action, const core::Game &game,
        [[maybe_unused]] std::optional<effects::EffectContext> context) const
    {
        if ([[maybe_unused]] const auto *block_action =
                dynamic_cast<const core::BlockAction *>(&action))
        {
            auto blocker{block_action->getBlocker()};

            // check condition for blocker
            EffectContext block_context{blocker};

            std::cout << "Checking block prevention effect condition\n";
            if (getCondition()->isSatisfied(game, block_context))
            {
                return true;
            }
        }
        return false;
    }
} // namespace dandan::effects
