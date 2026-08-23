#include "dandan/triggers/ETBtrigger.h"
#include "dandan/events/ETBEvent.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
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

    const auto registered = []
    {
        registerETBTrigger<false>("ETBtrigger");
        registerETBTrigger<true>("SelfETBTrigger");
        return true;
    }();
} // namespace
#endif

namespace dandan::triggers
{
    template <bool self_trigger>
    [[nodiscard]] bool ETBTrigger<self_trigger>::triggersOn(
        const events::IEvent &other,
        [[maybe_unused]] abilities::AbilityContext context) const
    {

        const auto *otherETB = dynamic_cast<const events::ETBEvent *>(&other);

        if (otherETB == nullptr)
        {
            return false;
        }

        if constexpr (self_trigger)
        {

            if (context.source_card_id.getID() != otherETB->source().getID())
            {
                return false;
            }
        }

        if (m_tapped.has_value() && otherETB->isTapped() != m_tapped.value())
        {
            return false;
        }

        return true;
    }

} // namespace dandan::triggers
