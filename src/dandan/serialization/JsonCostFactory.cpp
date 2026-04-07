#include "dandan/serialization/JsonCostFactory.h"
#include "dandan/costs/CyclingCost.h"
#include "dandan/costs/GenericManaCost.h"
#include "dandan/costs/ICost.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization {
nlohmann::json
JsonFactory<costs::ICost>::create_json(const costs::ICost *cost) {
  if (const auto *cycle_cost = dynamic_cast<const costs::CyclingCost *>(cost)) {
    auto j = nlohmann::json{{"type", "CyclingCost"},
                            {"data", nlohmann::json::object()}};

    const auto inner_cost = cycle_cost->getInnerCost();
    j["data"]["inner_cost"] = create_json(inner_cost);
    return j;
  } else if (const auto *generic_cost =
                 dynamic_cast<const costs::GenericManaCost *>(cost)) {
    auto j = nlohmann::json{{"type", "GenericManaCost"},
                            {"data", nlohmann::json::object()}};
    j["data"]["amount"] = generic_cost->getAmount();
    return j;
  } else {
    throw std::runtime_error("Unknown cost type for JSON serialization");
  }
}

std::unique_ptr<costs::ICost>
JsonFactory<costs::ICost>::create_product(const nlohmann::json &j) {
  const auto &type = j.at("type").get<std::string>();
  const auto &data = j.at("data");

  if (type == "CyclingCost") {
    auto generic_cost_json = data.at("generic_mana_cost");
    auto generic_cost = create_product(generic_cost_json);
    return std::make_unique<costs::CyclingCost>(std::move(generic_cost));
  } else if (type == "GenericManaCost") {
    auto amount = data.at("amount").get<int>();
    return std::make_unique<costs::GenericManaCost>(amount);
  } else {
    throw std::runtime_error("Unknown cost type for JSON deserialization");
  }
}
} // namespace dandan::serialization