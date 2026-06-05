#include "dandan/serialization/JsonTriggerFactory.h"
#ifdef DANDAN_SERIALIZE
#include "dandan/triggers/ETBtrigger.h"
#include "dandan/triggers/ITrigger.h"
#include "dandan/triggers/SelfETBtrigger.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<triggers::ITrigger>::create_json(
        const triggers::ITrigger *trigger)
    {
        if (const auto *selfETBTrigger =
                dynamic_cast<const triggers::SelfETBTrigger *>(trigger))
        {
            auto json = nlohmann::json{{"type", "SelfETBTrigger"},
                                       {"data", nlohmann::json::object()}};
            if (selfETBTrigger->isTapped())
            {
                json["data"]["tapped"] = selfETBTrigger->isTapped();
            }
            return json;
        }
        if (dynamic_cast<const triggers::ETBTrigger *>(trigger) != nullptr)
        {
            return nlohmann::json{{"type", "ETBTrigger"},
                                  {"data", nlohmann::json::object()}};
        }

        throw std::runtime_error("Unknown trigger type");
    }

    std::unique_ptr<triggers::ITrigger> JsonFactory<
        triggers::ITrigger>::create_product(const nlohmann::json &json)
    {
        const auto &type = json.at("type").get<std::string>();
        const auto &data = json.at("data");

        if (type == "SelfETBTrigger")
        {
            auto trigger = std::make_unique<triggers::SelfETBTrigger>();
            if (data.contains("tapped"))
            {
                trigger->setTapped(data["tapped"].get<bool>());
            }
            return trigger;
        }
        if (type == "ETBTrigger")
        {
            return std::make_unique<triggers::ETBTrigger>();
        }

        throw std::runtime_error("Unknown trigger type: " + type);
    }
} // namespace dandan::serialization
#endif // DANDAN_SERIALIZE