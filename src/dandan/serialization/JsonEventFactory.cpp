#include "dandan/serialization/JsonEventFactory.h"
#include "dandan/events/NoIslandsEvent.h"
#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/events/ETBEvent.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<events::IEvent>::create_json(
        const events::IEvent *event)
    {
        if (const auto *entersBattlefieldEvent =
                dynamic_cast<const events::ETBEvent *>(event))
        {
            auto json = nlohmann::json{{"type", "EntersBattlefieldEvent"},
                                       {"data", nlohmann::json::object()}};
            if (entersBattlefieldEvent->m_tapped.has_value())
            {
                json["data"]["tapped"] =
                    entersBattlefieldEvent->m_tapped.value();
            }
            return json;
        }
        if (dynamic_cast<const events::NoIslandsEvent *>(event) != nullptr)
        {
            return nlohmann::json{{"type", "NoIslandsEvent"},
                                  {"data", nlohmann::json::object()}};
        }

        throw std::runtime_error("Unknown event type");
    }

    std::unique_ptr<events::IEvent> JsonFactory<events::IEvent>::create_product(
        const nlohmann::json &json)
    {
        const auto &type = json.at("type").get<std::string>();
        const auto &data = json.at("data");

        if (type == "EntersBattlefieldEvent")
        {
            auto event = std::make_unique<events::ETBEvent>();
            if (data.contains("tapped"))
            {
                event->setTapped(data["tapped"].get<bool>());
            }
            return event;
        }
        if (type == "NoIslandsEvent")
        {
            return std::make_unique<events::NoIslandsEvent>();
        }

        throw std::runtime_error("Unknown event type: " + type);
    }
} // namespace dandan::serialization
#endif // DANDAN_BUILD_SERIALIZE