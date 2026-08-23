#include "dandan/abilities/EventTriggeredAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

#ifdef DANDAN_SERIALIZE
#include "dandan/abilities/StateTriggeredAbility.h"
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
    using namespace dandan::triggers;

    const auto registered = []
    {
        AbilityRegistry::instance().registerType<EventTriggeredAbility>(
            "TriggeredAbility",
            [](const IAbility *ability)
            {
                auto json = nlohmann::json::object();
                const auto *triggered{
                    dynamic_cast<const EventTriggeredAbility *>(ability)};

                json["trigger"] =
                    JsonFactory<ITrigger>::create_json(triggered->trigger());
                json["effect"] =
                    JsonFactory<IOneShotEffectDefinition>::create_json(
                        triggered->getEffect());
                json["kind"] = "event";

                return json;
            },
            [](const nlohmann::json &json) -> std::unique_ptr<IAbility>
            {
                auto kind{json.at("kind").get<std::string>()};
                if (kind == "event")
                {
                    auto trigger{JsonFactory<ITrigger>::create_product(
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

    EventTriggeredAbility::EventTriggeredAbility(
        std::unique_ptr<dandan::triggers::ITrigger> trigger,
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition> effect)
        : m_trigger(std::move(trigger)), m_effect(std::move(effect))
    {
    }

    [[nodiscard]] bool EventTriggeredAbility::appliesTo(
        const events::IEvent &event, abilities::AbilityContext context) const
    {
        return m_trigger->triggersOn(event, std::move(context));
    }

    /** Get the trigger for the ability as a const pointer
     * @return The trigger for the ability
     */
    [[nodiscard]] const dandan::triggers::ITrigger *EventTriggeredAbility::
        trigger() const
    {
        return m_trigger.get();
    }

    /** Get the trigger for the ability as a mutable pointer
     * @return The trigger for the ability
     */
    [[nodiscard]] dandan::triggers::ITrigger *EventTriggeredAbility::trigger()
    {
        return m_trigger.get();
    }

    /** Get the effect of the ability
     * @return The effect of the ability
     */
    [[nodiscard]] const dandan::effects::IOneShotEffectDefinition *
    EventTriggeredAbility::getEffect() const
    {
        return m_effect.get();
    }
    std::unique_ptr<effects::IOneShotEffect> EventTriggeredAbility::
        createEffect([[maybe_unused]] core::Game &game,
                     [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving triggered ability\n";
        return m_effect->bind(game,
                              effects::EffectContext(context.controller_id));
    }

} // namespace dandan::abilities
