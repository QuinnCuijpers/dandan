#include "dandan/effects/one_shot/SpinToTopEffect.h"
#include "dandan/core/TargetRequirement.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{

    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::abilities;
    using namespace dandan::core;
    using namespace dandan::numbers;

    const auto registered = []
    {
        OneShotEffectRegistry::instance()
            .registerType<SpinToTopEffectDefinition>(
                "SpinToTopEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<SpinToTopEffectDefinition>(
                        TargetRequirement{target_specs});
                });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    SpinToTopEffect::SpinToTopEffect(core::Target target, EffectContext context)
        : IOneShotEffect(std::move(context)), m_target(std::move(target))
    {
    }

    [[nodiscard]] std::unique_ptr<IOneShotEffect> SpinToTopEffect::copy() const
    {
        return std::make_unique<SpinToTopEffect>(m_target, getEffectContext());
    }

    std::unique_ptr<events::IEvent> SpinToTopEffect::apply_impl(
        core::Game &game) const
    {
        if (!std::holds_alternative<core::CardID>(m_target))
        {
            throw std::runtime_error(
                "Spin to top effect target is not a card ID");
        }
        auto permanent{std::get<core::CardID>(m_target)};
        auto *card{game.getCardByID(permanent)};
        game.moveCardFromZone(game.activePlayer(), *card);
        game.library().addCardTop(*card);
        return nullptr;
    }

} // namespace dandan::effects
