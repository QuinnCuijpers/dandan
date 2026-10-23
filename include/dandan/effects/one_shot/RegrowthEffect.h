#ifndef DANDAN_REGROWTHEFFECT_H
#define DANDAN_REGROWTHEFFECT_H

#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <utility>

namespace dandan::effects
{
    class RegrowthEffect : public IOneShotEffect
    {
    public:
        RegrowthEffect(std::vector<core::Type> filter_types,
                       core::PlayerID player_id, EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        std::vector<core::Type> m_filter_types;
        core::PlayerID m_player_id;
    };

    class RegrowthEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        explicit RegrowthEffectDefinition(
            std::vector<dandan::core::Type> filter_types);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override;

        [[nodiscard]] const std::vector<dandan::core::Type> &getFilterTypes()
            const;

    private:
        std::vector<dandan::core::Type> m_filter_types;
    };
} // namespace dandan::effects

#ifdef DANDAN_SERIALIZE
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

    inline const auto registeredRegrowthEffect = []
    {
        OneShotEffectRegistry::instance()
            .registerType<RegrowthEffectDefinition>(
                "RegrowthEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *regrowth =
                        dynamic_cast<const RegrowthEffectDefinition *>(effect);
                    json["filter_types"] = nlohmann::json::array();
                    for (auto type : regrowth->getFilterTypes())
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

                    return std::make_unique<RegrowthEffectDefinition>(
                        std::move(filter_types));
                });
        return true;
    }();
} // namespace dandan::serialization::registration
#endif

#endif
