#ifndef DANDAN_ENTERSTAPPEDEFFECT_H
#define DANDAN_ENTERSTAPPEDEFFECT_H

#include "IReplacementEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"

namespace dandan::effects
{
    /** @brief A replacement effect that causes a permanent to enter the battlefield
     * tapped. It listens to `ETBEvent`s and replaces the event with a modified
     * version that causes the permanent to enter tapped.
     * @class EntersTappedEffect
     *
     * @implements IReplacementEffect
     */
    struct EntersTappedEffect final : public IReplacementEffect
    {
        [[nodiscard]] bool appliesTo(
            const effects::IOneShotEffect &effect) const override;
        [[nodiscard]] effects::IOneShotEffect &replace(
            dandan::effects::IOneShotEffect &effect) const override;
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

    inline const auto registeredEntersTappedEffect = []
    {
        ContinuousEffectRegistry::instance().registerType<EntersTappedEffect>(
            "EntersTappedEffect",
            []([[maybe_unused]] const dandan::effects::IContinuousEffect
                   *effect)
            {
                auto json = nlohmann::json::object();
                return json;
            },
            []([[maybe_unused]] const nlohmann::json &json)
            { return std::make_unique<EntersTappedEffect>(); });
        return true;
    }();
} // namespace
#endif

#endif
