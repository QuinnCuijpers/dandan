
#ifndef DANDAN_STATETRIGGEREDABILITY_H
#define DANDAN_STATETRIGGEREDABILITY_H

#include "dandan/abilities/IAbility.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
namespace dandan::abilities
{
    /** @brief A triggered ability that activates when a specific condition
     * becomes satisfied.
     * @class StateTriggeredAbility
     *
     * @implements IAbility
     */
    class StateTriggeredAbility final : public IAbility
    {
    public:
        /** Constructor
         * @param condition The condition for the ability
         * @param effect The effect of the ability
         */
        StateTriggeredAbility(
            std::unique_ptr<conditions::ICondition> condition,
            std::unique_ptr<effects::IOneShotEffectDefinition> effect);

        /** Create an effect instance for this ability.
         * @param game The game instance.
         * @param context The ability context.
         * @return The created effect instance.
         */
        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            [[maybe_unused]] AbilityContext context) const override;

        /** Get the condition for the ability as a const pointer
         * @return The condition for the ability
         */
        [[nodiscard]] const conditions::ICondition *condition() const;

        /** Get the condition for the ability as a mutable pointer
         * @return The condition for the ability
         */
        [[nodiscard]] conditions::ICondition *condition();

        /** Get the effect of the ability
         * @return The effect of the ability
         */
        [[nodiscard]] const effects::IOneShotEffectDefinition *getEffect()
            const;

    private:
        std::unique_ptr<conditions::ICondition> m_condition;
        std::unique_ptr<effects::IOneShotEffectDefinition> m_effect;
    };
} // namespace dandan::abilities


#ifdef DANDAN_SERIALIZE
#include "dandan/abilities/EventTriggeredAbility.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization::registration::stateTriggeredAbility
{

    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::conditions;

    inline const auto registeredTriggeredAbility = []
    {
        AbilityRegistry::instance().registerType<StateTriggeredAbility>(
            "TriggeredAbility",
            [](const IAbility *ability)
            {
                auto json = nlohmann::json::object();
                const auto *state_triggered{
                    dynamic_cast<const StateTriggeredAbility *>(ability)};

                json["condition"] = JsonFactory<ICondition>::create_json(
                    state_triggered->condition());
                json["effect"] =
                    JsonFactory<IOneShotEffectDefinition>::create_json(
                        state_triggered->getEffect());
                json["kind"] = "state";

                return json;
            },
            [](const nlohmann::json &json) -> std::unique_ptr<IAbility>
            {
                auto kind{json.at("kind").get<std::string>()};
                if (kind == "event")
                {
                    auto trigger{
                        JsonFactory<dandan::triggers::ITrigger>::create_product(
                            json.at("trigger"))};

                    auto effect{
                        JsonFactory<IOneShotEffectDefinition>::create_product(
                            json.at("effect"))};

                    return std::make_unique<EventTriggeredAbility>(
                        std::move(trigger), std::move(effect));
                }

                if (kind == "state")
                {
                    auto condition{JsonFactory<dandan::conditions::ICondition>::
                                       create_product(json.at("condition"))};

                    auto effect{
                        JsonFactory<IOneShotEffectDefinition>::create_product(
                            json.at("effect"))};

                    return std::make_unique<StateTriggeredAbility>(
                        std::move(condition), std::move(effect));
                }
                throw std::runtime_error("Unknown kind for triggered ability");
            });

        return true;
    }();
} // namespace
#endif

#endif
