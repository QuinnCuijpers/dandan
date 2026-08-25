#include "dandan/effects/one_shot/ModalEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/serialization/JsonFactory.h"

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
        OneShotEffectRegistry::instance().registerType<ModalEffectDefinition>(
            "ModalEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *modal =
                    dynamic_cast<const ModalEffectDefinition *>(effect);
                json["options"] = nlohmann::json::array();
                for (const auto &option : modal->getOptions())
                {
                    json["options"].push_back(
                        JsonFactory<IOneShotEffectDefinition>::create_json(
                            option.get()));
                }

                return json;
            },
            [](const nlohmann::json &data,
               [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                std::vector<std::unique_ptr<IOneShotEffectDefinition>> options;
                std::transform(
                    data.at("options").begin(), data.at("options").end(),
                    std::back_inserter(options),
                    [](const auto &option_json)
                    {
                        return JsonFactory<IOneShotEffectDefinition>::
                            create_product(option_json);
                    });

                return std::make_unique<ModalEffectDefinition>(
                    std::move(options));
            });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<IOneShotEffect> ModalEffectDefinition::bind(
        const core::ExecutionContext exec_ctx, EffectContext context) const
    {
        auto &card_registry{exec_ctx.cards.get()};

        const auto *card{card_registry[context.card_id.value()]};
        std::cout << "Binding modal effect for card " << card->getData().name
                  << '\n';
        auto modal_choice{card->getModalChoice(*this)};
        return m_options.at(modal_choice)->bind(exec_ctx, context);
    }
} // namespace dandan::effects
