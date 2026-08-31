#include "dandan/effects/one_shot/ShowAndTellEffect.h"
#include "dandan/core/CardID.h"
#include "dandan/core/GameState.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/events/IEvent.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

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
            .registerType<ShowAndTellEffectDefinition>(
                "ShowAndTellEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<ShowAndTellEffectDefinition>(
                        TargetRequirement{target_specs});
                });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ShowAndTellEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        auto valid_type = [this, &card_registry](const core::CardID card_id)
        {
            auto *card{card_registry[card_id]};
            const auto *fit{std::find(m_types.begin(), m_types.end(),
                                      card->getData().type)};
            return (fit != m_types.end());
        };

        auto available_options{std::vector<core::CardID>{}};
        auto &player{game.getPlayer(m_player)};
        const auto &hand{player.hand().getCards()};
        std::copy_if(hand.begin(), hand.end(),
                     std::back_inserter(available_options), valid_type);

        game.printCards(available_options, card_registry);
        std::cout << "You may put an artifact, creature, enchantment, or land "
                     "card from your hand onto the battlefield.\n";
        std::cout << "Which card would you like to put onto the battlefield "
                     "[cardID || -1 for none]: ";
        std::string input{};
        std::getline(istream, input);
        if (input == "-1")
        {
            return nullptr;
        }

        auto card_id{core::CardID::fromInt(std::stoi(input))};

        auto *card{card_registry[card_id]};
        player.playCard(*card);

        return nullptr;
    }
} // namespace dandan::effects
