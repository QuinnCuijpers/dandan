#include "dandan/abilities/StateTriggeredAbility.h"
#include "dandan/abilities/EventTriggeredAbility.h"
#include <memory>
#include <stdexcept>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace
{

    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::conditions;

    const auto registered = []
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

namespace dandan::abilities
{
    StateTriggeredAbility::StateTriggeredAbility(
        std::unique_ptr<conditions::ICondition> condition,
        std::unique_ptr<effects::IOneShotEffectDefinition> effect)
        : m_condition(std::move(condition)), m_effect(std::move(effect))
    {
    }

    /** Create an effect instance for this ability.
     * @param game The game instance.
     * @param context The ability context.
     * @return The created effect instance.
     */
    [[nodiscard]] std::unique_ptr<effects::IOneShotEffect>
    StateTriggeredAbility::createEffect(
        core::ExecutionContext exec_ctx,
        [[maybe_unused]] AbilityContext context) const
    {
        return m_effect->bind(exec_ctx,
                              effects::EffectContext(context.source_card_id,
                                                     context.controller_id));
    }

    /** Get the condition for the ability as a const pointer
     * @return The condition for the ability
     */
    [[nodiscard]] const conditions::ICondition *StateTriggeredAbility::
        condition() const
    {
        return m_condition.get();
    }

    /** Get the condition for the ability as a mutable pointer
     * @return The condition for the ability
     */
    [[nodiscard]] conditions::ICondition *StateTriggeredAbility::condition()
    {
        return m_condition.get();
    }

    /** Get the effect of the ability
     * @return The effect of the ability
     */
    [[nodiscard]] const effects::IOneShotEffectDefinition *
    StateTriggeredAbility::getEffect() const
    {
        return m_effect.get();
    }

} // namespace dandan::abilities
