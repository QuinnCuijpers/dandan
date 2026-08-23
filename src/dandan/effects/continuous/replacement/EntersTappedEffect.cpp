#include "dandan/effects/continuous/replacement/EntersTappedEffect.h"
#include "dandan/effects/one_shot/ETBEffect.h"
#include <stdexcept>

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

namespace dandan::effects
{
    // TODO: simplify double dynamic_cast
    bool EntersTappedEffect::appliesTo(
        const effects::IOneShotEffect &effect) const
    {
        return dynamic_cast<const effects::ETBEffect *>(&effect) != nullptr;
    }

    effects::IOneShotEffect &EntersTappedEffect::replace(
        effects::IOneShotEffect &effect) const
    {
        std::cout << "Checking entertapped replacement effect\n";
        if (appliesTo(effect))
        {
            std::cout << "Applying etb tapped replacement effect\n";
            auto *etbEffect = dynamic_cast<effects::ETBEffect *>(&effect);
            etbEffect->setTapped(true);
            return *etbEffect;
        }

        throw std::runtime_error(
            "EntersTappedEffect can only replace ETB effects");
    }

} // namespace dandan::effects
