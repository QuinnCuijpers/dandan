#include "dandan/serialization/JsonEventFactory.h"
#include "dandan/events/EntersBattleFieldEvent.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization {
nlohmann::json
JsonFactory<events::IEvent>::create_json(const events::IEvent *event) {
  if (const auto *entersBattlefieldEvent =
          dynamic_cast<const events::EntersBattlefieldEvent *>(event)) {
    auto j = nlohmann::json{{"type", "EntersBattlefieldEvent"},
                            {"data", nlohmann::json()}};
    if (entersBattlefieldEvent->m_tapped.has_value()) {
      j["data"]["tapped"] = entersBattlefieldEvent->m_tapped.value();
    }
    return j;
  } else {
    throw std::runtime_error("Unknown event type");
  }
}

std::unique_ptr<events::IEvent>
JsonFactory<events::IEvent>::create_product(const nlohmann::json &j) {
  const auto &type = j.at("type").get<std::string>();
  const auto &data = j.at("data");

  if (type == "EntersBattlefieldEvent") {
    auto event = std::make_unique<events::EntersBattlefieldEvent>();
    if (data.contains("tapped")) {
      event->setTapped(data["tapped"].get<bool>());
    }
    return event;
  } else {
    throw std::runtime_error("Unknown event type: " + type);
  }
}
} // namespace dandan::serialization