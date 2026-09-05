#ifndef DANDAN_MODAL_EFFECT_H
#define DANDAN_MODAL_EFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace dandan::effects
{

    class ModalEffectDefinition : public IOneShotEffectDefinition
    {

    public:
        explicit ModalEffectDefinition(
            std::vector<std::unique_ptr<IOneShotEffectDefinition>> options)
            : m_options(std::move(options))
        {
        }

        [[nodiscard]] std::string display() const override
        {
            std::string result = "Choose one -\n";
            for (const auto &m_option : m_options)
            {
                result += "* " + m_option->display() + "\n";
            }
            return result;
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            core::ExecutionContext exec_ctx,
            EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            auto cloned_options{
                std::vector<std::unique_ptr<IOneShotEffectDefinition>>{}};

            std::transform(m_options.begin(), m_options.end(),
                           std::back_inserter(cloned_options),
                           [](const auto &option) { return option->clone(); });
            return std::make_unique<ModalEffectDefinition>(
                std::move(cloned_options));
        }

        [[nodiscard]] const std::vector<
            std::unique_ptr<IOneShotEffectDefinition>> &
        getOptions() const
        {
            return m_options;
        }

    private:
        std::vector<std::unique_ptr<IOneShotEffectDefinition>> m_options;
    };
} // namespace dandan::effects


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{

    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::abilities;
    using namespace dandan::core;
    using namespace dandan::numbers;

    inline const auto registeredModalEffect = []
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

#endif
