#include "dandan/effects/one_shot/SelfSacrificeEffect.h"

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
            .registerType<SelfSacrificeEffectDefinition>(
                "SelfSacrificeEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                { return std::make_unique<SelfSacrificeEffectDefinition>(); });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    SelfSacrificeEffect::SelfSacrificeEffect(core::CardID card_id,
                                             EffectContext context)
        : IOneShotEffect(std::move(context)), m_card_id(card_id)
    {
    }

    [[nodiscard]] std::unique_ptr<IOneShotEffect> SelfSacrificeEffect::copy()
        const
    {
        return std::make_unique<SelfSacrificeEffect>(m_card_id,
                                                     getEffectContext());
    }

    std::unique_ptr<events::IEvent> SelfSacrificeEffect::apply_impl(
        [[maybe_unused]] core::Game &game) const
    {
        auto *card{game.getCardByID(m_card_id)};
        card->destroy(game);
        return nullptr;
    }
} // namespace dandan::effects
