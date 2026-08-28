#include "dandan/abilities/StaticAbility.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace
{
    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::costs;
    using namespace dandan::mana;
    using namespace dandan::effects;

    const auto registered = []
    {
        AbilityRegistry::instance().registerType<StaticAbility>(
            "StaticAbility",
            [](const IAbility *ability)
            {
                auto json = nlohmann::json::object();
                const auto *static_ability{
                    dynamic_cast<const StaticAbility *>(ability)};

                json["static_type"] = static_ability->getType();

                json["continuous_effect"] =
                    JsonFactory<IContinuousEffect>::create_json(
                        static_ability->getEffect());
                return json;
            },
            [](const nlohmann::json &json)
            {
                auto static_type{
                    json.at("static_type").get<StaticAbility::Type>()};

                auto continuous_effect{
                    JsonFactory<IContinuousEffect>::create_product(
                        json.at("continuous_effect"))};

                return std::make_unique<StaticAbility>(
                    static_type, std::move(continuous_effect));
            });

        return true;
    }();
} // namespace
#endif

namespace dandan::abilities
{

    StaticAbility::StaticAbility(
        Type type, std::unique_ptr<effects::IContinuousEffect> effect)
        : m_type(type), m_effect(std::move(effect))
    {
    }

    std::unique_ptr<effects::IOneShotEffect> StaticAbility::createEffect(
        [[maybe_unused]] core::ExecutionContext exec_ctx,
        [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving StaticAbility\n";
        return nullptr;
    }

    [[nodiscard]] StaticAbility::Type StaticAbility::getType() const
    {
        return m_type;
    }

    [[nodiscard]] const effects::IContinuousEffect *StaticAbility::getEffect()
        const
    {
        return m_effect.get();
    }
} // namespace dandan::abilities
