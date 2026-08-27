#include "dandan/effects/one_shot/MillEffect.h"
#include "dandan/core/Game.h"
#include "dandan/utils/convertToWords.h"

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
        OneShotEffectRegistry::instance().registerType<MillEffectDefinition>(
            "MillEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *mill =
                    dynamic_cast<const MillEffectDefinition *>(effect);
                json["amount"] = mill->getAmount();
                return json;
            },
            [](const nlohmann::json &data,
               const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                return std::make_unique<MillEffectDefinition>(
                    data.at("amount").get<int>(),
                    dandan::core::TargetRequirement{target_specs});
            });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> MillEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        auto context{getEffectContext()};
        auto milled_cards{game.library().mill(exec_ctx, m_amount)};
        if (context.card_id.has_value())
        {
            auto card_id{context.card_id.value()};
            if (milled_cards.size() == 1)
            {
                auto *card{card_registry[card_id]};
                auto milled_id{milled_cards[0]};
                const auto &name{card_registry[milled_id]->getData().name};
                card->remember("milledCardName", name);
            }
        }
        return nullptr;
    }

    std::string MillEffectDefinition::display() const
    {
        return "Target player mills " + utils::convertToWords(m_amount) +
               " card" + (m_amount > 1 ? "s" : "");
    }
} // namespace dandan::effects
