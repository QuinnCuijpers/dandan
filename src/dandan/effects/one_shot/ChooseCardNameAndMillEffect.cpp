#include "dandan/effects/one_shot/ChooseCardNameAndMillEffect.h"
#include "dandan/core/Game.h"
#include "dandan/core/PlayerID.h"
#include "dandan/effects/one_shot/MillEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <string>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{

    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::abilities;
    using namespace dandan::core;

    const auto registered = []
    {
        OneShotEffectRegistry::instance()
            .registerType<ChooseCardNameAndMillEffectDefinition>(
                "ChooseCardNameAndMillEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *choose_name_and_mill = dynamic_cast<
                        const ChooseCardNameAndMillEffectDefinition *>(effect);
                    json["amount"] = choose_name_and_mill->getAmount();
                    return json;
                },
                [](const nlohmann::json &data,
                   const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<
                        ChooseCardNameAndMillEffectDefinition>(
                        data.at("amount").get<int>(),
                        TargetRequirement{target_specs});
                });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ChooseCardNameAndMillEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {

        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        auto *card{card_registry[m_source]};
        auto player_id = std::get<core::PlayerID>(m_target);
        std::cout << "Choose a card name, then "
                  << game.getPlayer(player_id).getName() << " mills a card.\n";
        std::cout << "Card Name: ";

        std::string input{};
        std::getline(game.istream(), input);

        card->remember("chosenCardName", input);

        auto mill_effect{std::make_unique<MillEffect>(m_amount, player_id,
                                                      getEffectContext())};
        auto mill_event{mill_effect->apply_impl(exec_ctx)};
        return mill_event;
    }
} // namespace dandan::effects
