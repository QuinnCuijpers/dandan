#ifndef DANDAN_FLYINGABILITY_H
#define DANDAN_FLYINGABILITY_H

#include "dandan/abilities/keywords/IKeyWordAbility.h"
#include "dandan/abilities/keywords/Keyword.h"
#include <memory>
namespace dandan::abilities
{
    class FlyingAbility : public IKeyWordAbility
    {
    public:
        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::ExecutionContext exec_ctx,
            AbilityContext context) const override
        {
            return nullptr;
        }

        [[nodiscard]] std::unique_ptr<IAbility> clone() const override
        {
            return std::make_unique<FlyingAbility>();
        }

        [[nodiscard]] Keyword keyword() const override
        {
            return Keyword::Flying;
        }

    private:
    };
} // namespace dandan::abilities

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization::registration
{

    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::effects;

    inline const auto registeredFlyingAbility = []
    {
        AbilityRegistry::instance().registerType<FlyingAbility>(
            "FlyingAbility",
            []([[maybe_unused]] const IAbility *ability)
            {
                auto json = nlohmann::json::object();
                return json;
            },
            []([[maybe_unused]] const nlohmann::json &json)
            { return std::make_unique<FlyingAbility>(); });

        return true;
    }();
} // namespace dandan::serialization::registration
#endif

#endif // !DANDAN_FLYINGABILITY_H
