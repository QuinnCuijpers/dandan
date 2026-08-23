#include "dandan/core/Expire.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/serialization/JsonFactory.h"
#include <optional>
#include <vector>
#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include "nlohmann/json_fwd.hpp"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<effects::IOneShotEffectDefinition>::create_json(
        const effects::IOneShotEffectDefinition *effect)
    {
        auto json = nlohmann::json::object();
        const auto &registration{
            OneShotEffectRegistry::instance().serializerFor(*effect)};

        auto data = registration.serializer(effect);

        if (registration.representation == JsonRepresentation::INLINE)
        {
            return data;
        }

        json["type"] = registration.name;
        json["data"] = data;

        if (effect->readLinks().has_value())
        {
            for (const auto &read_link : effect->readLinks().value())
            {
                json["data"]["reads"].push_back(read_link);
            }
        }

        if (effect->writeLinks().has_value())
        {
            for (const auto &write_link : effect->writeLinks().value())
            {
                json["data"]["writes"].push_back(write_link);
            }
        }

        if (auto expire = effect->expires(); expire != core::ExpireTime::None)
        {
            json["data"]["expires"] = expire;
        }

        if (const auto *targets = effect->getTargetRequirement())
        {
            json["data"]["targets"] = nlohmann::json::array();
            for (const auto &target_types : targets->getTargetTypes())
            {
                auto target_obj = nlohmann::json::object();
                target_obj["types"] = target_types.types;
                if (target_types.controller != core::Controller::Any)
                {
                    target_obj["controller"] = target_types.controller;
                }
                if (target_types.source == core::TargetSource::Linked &&
                    target_types.key.has_value())
                {
                    target_obj["reads"] = target_types.key.value();
                }
                json["data"]["targets"].push_back(target_obj);
            }
        }

        return json;
    }

    std::unique_ptr<effects::IOneShotEffectDefinition> JsonFactory<
        effects::IOneShotEffectDefinition>::create_product(const nlohmann::json
                                                               &json)
    {
        const auto &type = json.at("type").get<std::string>();
        const auto &targets = json["data"].find("targets");
        const auto &expire = json["data"].find("expires");
        auto expiry{core::ExpireTime::None};
        std::vector<core::TargetSpec> target_specs;

        if (targets != json["data"].end())
        {
            for (const auto &target_json : *targets)
            {
                if (!target_json.at("types").is_array())
                {
                    throw std::runtime_error(
                        "Expected 'types' to be an array, got: " +
                        target_json.at("types").dump());
                }
                auto types{target_json.at("types")
                               .get<std::vector<dandan::core::TargetType>>()};

                if (target_json.contains("controller"))
                {
                    core::Controller controller{target_json.at("controller")};
                    core::TargetSpec target_spec{types, controller};
                    target_specs.emplace_back(target_spec);
                }
                else
                {
                    target_specs.emplace_back(types);
                }
            }
        }

        if (expire != json["data"].end())
        {
            expiry = json["data"].at("expires");
        }

        return OneShotEffectRegistry::instance().deserializerFor(type)(
            json.at("data"), target_specs, expiry);
    }

} // namespace dandan::serialization
#endif // DANDAN_SERIALIZE
