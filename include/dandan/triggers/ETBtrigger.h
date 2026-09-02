
#ifndef DANDAN_ETBTRIGGER_H
#define DANDAN_ETBTRIGGER_H

#include "ITrigger.h"
#include "dandan/events/ETBEvent.h"
#include "dandan/events/IEvent.h"
#include <optional>

namespace dandan::triggers
{
    /** @brief A trigger that activates when a card enters the battlefield.
     * @class ETBTrigger
     *
     * @implements ITrigger
     */
    template <bool self_trigger = false> class ETBTrigger : public ITrigger
    {
    public:
        ETBTrigger() = default;

        /** Sets whether to only trigger on tapped ETB events or not.
         * @param tapped The tapped status to set.
         */
        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

        /** Returns whether the trigger is set to only trigger on tapped ETB
         * events.
         * @return True if the trigger is set to only trigger on tapped ETB
         * events, false otherwise.
         */
        [[nodiscard]] bool isTapped() const
        {
            return m_tapped.value_or(false);
        }

        [[nodiscard]] bool triggersOn(
            const events::IEvent &other,
            [[maybe_unused]] abilities::AbilityContext context) const override
        {

            const auto *otherETB =
                dynamic_cast<const events::ETBEvent *>(&other);

            if (otherETB == nullptr)
            {
                return false;
            }

            if constexpr (self_trigger)
            {

                if (context.source_card_id.getID() !=
                    otherETB->source().getID())
                {
                    return false;
                }
            }

            if (m_tapped.has_value() &&
                otherETB->isTapped() != m_tapped.value())
            {
                return false;
            }

            return true;
        }

    private:
        std::optional<bool> m_tapped;
    };

    using SelfETBTrigger = ETBTrigger<true>;

} // namespace dandan::triggers

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
#include <string>
namespace dandan::serialization::registration
{
    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::conditions;
    using namespace dandan::triggers;

    template <bool Self> void registerETBTrigger(const std::string &name)
    {
        TriggerRegistry::instance().registerType<ETBTrigger<Self>>(
            name,
            [](const ITrigger *trigger)
            {
                auto json = nlohmann::json::object();
                const auto *etb =
                    dynamic_cast<const ETBTrigger<Self> *>(trigger);
                if (etb)
                {
                    json["tapped"] = etb->isTapped();
                }
                return json;
            },
            [](const nlohmann::json &json)
            {
                auto trigger = std::make_unique<ETBTrigger<Self>>();
                if (json.contains("tapped"))
                {
                    trigger->setTapped(json["tapped"].get<bool>());
                }
                return trigger;
            });
    }

    inline const auto registeredEtbTrigger = []
    {
        registerETBTrigger<false>("ETBtrigger");
        return true;
    }();

    inline const auto registeredSelfEtbTrigger = []
    {
        registerETBTrigger<true>("SelfETBTrigger");
        return true;
    }();
} // namespace dandan::serialization::registration
#endif

#endif
