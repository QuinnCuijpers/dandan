#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/numbers/ExactNumber.h"

#include "dandan/core/Game.h"
#include "dandan/serialization/JsonFactory.h"
#include "dandan/utils/convertToWords.h"
#include <iostream>
#include <memory>

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
        OneShotEffectRegistry::instance().registerType<DrawEffectDefinition>(
            "DrawEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *draw_effect =
                    dynamic_cast<const DrawEffectDefinition *>(effect);
                auto *number{draw_effect->getNumber().get()};
                if (const auto *exactNumber =
                        dynamic_cast<const ExactNumber *>(number))
                {
                    json["amount"] = exactNumber->getValue();
                }
                else
                {
                    json["amount"] = JsonFactory<INumber>::create_json(number);
                }
                return json;
            },
            [](const nlohmann::json &data,
               [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                const auto &amount_json = data.at("amount");
                if (amount_json.is_number_integer())
                {
                    return std::make_unique<DrawEffectDefinition>(
                        amount_json.get<int>());
                }
                auto amount = JsonFactory<INumber>::create_product(amount_json);
                return std::make_unique<DrawEffectDefinition>(
                    std::move(amount));
            });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{

    std::string DrawEffectDefinition::display() const
    {
        if (const auto *fixed =
                dynamic_cast<const numbers::ExactNumber *>(m_amount.get()))
        {
            std::string res{};
            if (fixed->getValue() == 1)
            {
                res += "Draw a card";
            }
            else
            {
                res += "Draw " + utils::convertToWords(fixed->getValue()) +
                       " cards";
            }

            return res;
        }
        throw std::runtime_error("Unknown INumber type in DrawEffect display");
        // return "Draw " + m_amount->display() + " cards";
    }

    std::unique_ptr<events::IEvent> DrawEffect::apply_impl(
        [[maybe_unused]] core::Game &game) const
    {
        int value{m_amount->getValue(game, getEffectContext())};

        if (value == 1)
        {
            std::cout << "Applying draw effect\n";
            auto &player{game.getPlayer(getEffectContext().player_id.value())};
            player.drawCard(game);
            return nullptr;
        }
        // Break down the draw effect into multiple single card draws to
        // trigger any relevant state triggers

        std::cout << "Applying draw effect for " << value << " cards\n";
        for (int i = 0; i < value; ++i)
        {
            auto draw_definition{std::make_unique<DrawEffectDefinition>(1)};
            auto &player{game.getPlayer(getEffectContext().player_id.value())};
            auto draw_effect{
                draw_definition->bind(game, EffectContext{player.getID()})};

            // breaking effect up doesnt require checking replacement effects as
            // all underlying effects are checked
            draw_effect->apply(game);
        }

        return nullptr;
    }

} // namespace dandan::effects
