#ifndef DANDAN_TUTOR_TOP_EFFECT_H
#define DANDAN_TUTOR_TOP_EFFECT_H

#include <utility>

#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    class TutorTopEffect : public IOneShotEffect
    {
    public:
        TutorTopEffect(std::vector<core::Type> filter_types,
                       core::PlayerID player_id, EffectContext context)
            : IOneShotEffect(std::move(context)),
              m_filter_types(std::move(filter_types)), m_player_id(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<TutorTopEffect>(m_filter_types, m_player_id,
                                                    getEffectContext());
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        std::vector<core::Type> m_filter_types;
        core::PlayerID m_player_id;
    };

    class TutorTopEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        explicit TutorTopEffectDefinition(
            std::vector<dandan::core::Type> filter_types)
            : m_filter_types(std::move(filter_types))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::ExecutionContext exec_ctx,
            EffectContext context) const override
        {
            return std::make_unique<TutorTopEffect>(
                m_filter_types, context.player_id.value(), context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<TutorTopEffectDefinition>(m_filter_types);
        }

        [[nodiscard]] const std::vector<dandan::core::Type> &getFilterTypes()
            const
        {
            return m_filter_types;
        }

    private:
        std::vector<dandan::core::Type> m_filter_types;
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
    using namespace dandan::abilities;
    using namespace dandan::core;
    using namespace dandan::numbers;

    inline const auto registeredTutorTopEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<TutorTopEffectDefinition>(
                "TutorTopEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *tutor =
                        dynamic_cast<const TutorTopEffectDefinition *>(effect);
                    json["filter_types"] = nlohmann::json::array();
                    for (auto type : tutor->getFilterTypes())
                    {
                        json["filter_types"].push_back(type);
                    }
                    return json;
                },
                [](const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    std::vector<Type> filter_types;
                    std::transform(data.at("filter_types").begin(),
                                   data.at("filter_types").end(),
                                   std::back_inserter(filter_types),
                                   [](const auto &type_json)
                                   { return type_json.template get<Type>(); });

                    return std::make_unique<TutorTopEffectDefinition>(
                        std::move(filter_types));
                });
        return true;
    }();
} // namespace
#endif

#endif
