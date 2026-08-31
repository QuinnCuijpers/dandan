#ifndef DANDAN_EVENTTRIGGEREDABILITY_H
#define DANDAN_EVENTTRIGGEREDABILITY_H

#include "IAbility.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/triggers/ITrigger.h"
#include <memory>

namespace dandan::abilities
{
    /** @brief A triggered ability that activates when a specific trigger event
     * occurs.
     * @class EventTriggeredAbility
     *
     * @implements IAbility
     */
    class EventTriggeredAbility final : public IAbility
    {
    public:
        /** Constructor
         * @param trigger The trigger for the ability
         * @param effect The effect of the ability
         */
        EventTriggeredAbility(
            std::unique_ptr<dandan::triggers::ITrigger> trigger,
            std::unique_ptr<dandan::effects::IOneShotEffectDefinition> effect);

        /** Check if the triiggered ability applies to a given event and
         * context.
         * @param event The event to check.
         * @param context The ability context.
         * @return True if the ability applies, false otherwise.
         */
        [[nodiscard]] bool appliesTo(const events::IEvent &event,
                                     abilities::AbilityContext context) const;

        /** Get the trigger for the ability as a const pointer
         * @return The trigger for the ability
         */
        [[nodiscard]] const dandan::triggers::ITrigger *trigger() const;

        /** Get the trigger for the ability as a mutable pointer
         * @return The trigger for the ability
         */
        [[nodiscard]] dandan::triggers::ITrigger *trigger();

        /** Get the effect of the ability
         * @return The effect of the ability
         */
        [[nodiscard]] const dandan::effects::IOneShotEffectDefinition *
        getEffect() const;

        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::ExecutionContext exec_ctx,
            AbilityContext context) const override;

    private:
        std::unique_ptr<dandan::triggers::ITrigger> m_trigger;
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition> m_effect;
    };
} // namespace dandan::abilities


#ifdef DANDAN_SERIALIZE
#include "dandan/abilities/StateTriggeredAbility.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization::registration::eventTriggeredAbility
{

    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::conditions;
    using namespace dandan::triggers;

    inline const auto registeredTriggeredAbility = []
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

#endif
