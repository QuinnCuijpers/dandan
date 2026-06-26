#include "dandan/serialization/JsonEffectOneShotFactory.h"
#include "dandan/core/CardData.h"
#include "dandan/core/Expire.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/one_shot/BounceEffect.h"
#include "dandan/effects/one_shot/ChooseCardNameAndMillEffect.h"
#include "dandan/effects/one_shot/MemoryLapseEffect.h"
#include "dandan/effects/one_shot/MindBendEffect.h"
#include <algorithm>
#include <iterator>
#include <optional>
#include <vector>
#ifdef DANDAN_SERIALIZE
#include "dandan/effects/one_shot/BounceLandEffect.h"
#include "dandan/effects/one_shot/ChangeLandTypeEffect.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/effects/one_shot/ExileTopEffect.h"
#include "dandan/effects/one_shot/MillEffect.h"
#include "dandan/effects/one_shot/ModalEffect.h"
#include "dandan/effects/one_shot/OptionalDrawEffect.h"
#include "dandan/effects/one_shot/PeekEffect.h"
#include "dandan/effects/one_shot/PutCardOnTopEffect.h"
#include "dandan/effects/one_shot/ScryEffect.h"
#include "dandan/effects/one_shot/SelfSacrificeEffect.h"
#include "dandan/effects/one_shot/TimeTwisterEffect.h"
#include "dandan/effects/one_shot/TutorTopEffect.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "nlohmann/json_fwd.hpp"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<effects::IOneShotEffectDefinition>::create_json(
        const effects::IOneShotEffectDefinition *effect)
    {
        auto json = nlohmann::json::object();
        json["data"] = nlohmann::json::object();

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
                json["data"]["targets"].push_back({{"types", target_types}});
            }
        }

        if (const auto *ModalEffect =
                dynamic_cast<const effects::ModalEffectDefinition *>(effect))
        {
            json["type"] = "ModalEffect";
            json["data"]["options"] = nlohmann::json::array();
            for (const auto &option : ModalEffect->getOptions())
            {
                json["data"]["options"].push_back(create_json(option.get()));
            }
            return json;
        }
        if (const auto *scryEffect =
                dynamic_cast<const effects::ScryEffectDefinition *>(effect))
        {
            json["type"] = "ScryEffect";
            json["data"]["scry_amount"] = scryEffect->getScryAmount();
            return json;
        }
        if (const auto *peekEffect =
                dynamic_cast<const effects::PeekEffectDefinition *>(effect))
        {
            json["type"] = "PeekEffect";
            json["data"]["peek_amount"] = peekEffect->getPeekAmount();
            return json;
        }
        if (const auto *drawEffect =
                dynamic_cast<const effects::DrawEffectDefinition *>(effect))
        {
            json["type"] = "DrawEffect";
            auto *number{drawEffect->getNumber().get()};
            if (const auto *exactNumber =
                    dynamic_cast<const numbers::ExactNumber *>(number))
            {
                json["data"]["amount"] = exactNumber->getValue();
            }
            else
            {
                json["data"]["amount"] =
                    JsonFactory<numbers::INumber>::create_json(number);
            }
            return json;
        }
        if ([[maybe_unused]] const auto *bounceLandEffect =
                dynamic_cast<const effects::BounceLandEffectDefinition *>(
                    effect))
        {
            json["type"] = "BounceLandEffect";
            return json;
        }
        if (dynamic_cast<const effects::SelfSacrificeEffectDefinition *>(
                effect) != nullptr)
        {
            json["type"] = "SelfSacrificeEffect";
            return json;
        }
        if (const auto *putCardOnTopEffect =
                dynamic_cast<const effects::PutCardOnTopEffectDefinition *>(
                    effect))
        {
            json["type"] = "PutCardOnTopEffect";
            json["data"]["amount"] = putCardOnTopEffect->getAmount();
            return json;
        }

        if (dynamic_cast<const effects::TimeTwisterEffectDefinition *>(
                effect) != nullptr)
        {
            json["type"] = "TimeTwisterEffect";
            return json;
        }

        if (const auto *exileTopEffect =
                dynamic_cast<const effects::ExileTopEffectDefinition *>(effect))
        {
            json["type"] = "ExileTopEffect";
            json["data"]["amount"] = exileTopEffect->getAmount();
            return json;
        }

        if ([[maybe_unused]] const auto *optionalDrawEffect =
                dynamic_cast<const effects::OptionalDrawEffectDefinition *>(
                    effect))
        {
            json["type"] = "OptionalDrawEffect";
            json["data"]["amount"] = optionalDrawEffect->getAmount();
            json["data"]["each_player"] = optionalDrawEffect->isEachPlayer();
            return json;
        }

        if (const auto *tutorTopEffect =
                dynamic_cast<const effects::TutorTopEffectDefinition *>(effect))
        {
            json["type"] = "TutorTopEffect";
            json["data"]["filter_types"] = nlohmann::json::array();
            for (auto type : tutorTopEffect->getFilterTypes())
            {
                json["data"]["filter_types"].push_back(type);
            }
            return json;
        }

        if (const auto *millEffect =
                dynamic_cast<const effects::MillEffectDefinition *>(effect))
        {
            json["type"] = "MillEffect";
            json["data"]["amount"] = millEffect->getAmount();
            return json;
        }

        if (dynamic_cast<const effects::ChangeLandTypeEffectDefinition *>(
                effect) != nullptr)
        {
            json["type"] = "ChangeLandTypeEffect";
            return json;
        }
        if (dynamic_cast<const effects::MindBendEffectDefinition *>(effect) !=
            nullptr)
        {
            json["type"] = "MindBendEffect";
            return json;
        }
        if (dynamic_cast<const effects::BounceEffectDefinition *>(effect) !=
            nullptr)
        {
            json["type"] = "BounceEffect";
            return json;
        }
        if (dynamic_cast<const effects::MemoryLapseEffectDefinition *>(
                effect) != nullptr)
        {
            json["type"] = "MemoryLapseEffect";
            return json;
        }

        if (const auto *choose_name_and_mill = dynamic_cast<
                const effects::ChooseCardNameAndMillEffectDefinition *>(effect))
        {
            json["type"] = "ChooseCardNameAndMillEffect";
            json["data"]["amount"] = choose_name_and_mill->getAmount();
            return json;
        }

        throw std::runtime_error(
            "Unknown effect type for JSON serialization: " +
            std::string(typeid(*effect).name()));
    }

    std::unique_ptr<effects::IOneShotEffectDefinition> JsonFactory<
        effects::IOneShotEffectDefinition>::create_product(const nlohmann::json
                                                               &json)
    {
        // TODO: add read and write links
        const auto &type = json.at("type").get<std::string>();
        const auto &data = json.at("data");
        const auto &targets = json["data"].find("targets");
        const auto &expire = json["data"].find("expires");
        auto expiry{core::ExpireTime::None};
        std::vector<std::vector<dandan::core::TargetType>> target_types;

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
                target_types.push_back(types);
            }
        }

        if (expire != json["data"].end())
        {
            expiry = json["data"].at("expires");
        }

        if (type == "ModalEffect")
        {
            std::vector<std::unique_ptr<effects::IOneShotEffectDefinition>>
                options;
            std::transform(data.at("options").begin(), data.at("options").end(),
                           std::back_inserter(options),
                           [](const auto &option_json)
                           { return create_product(option_json); });

            return std::make_unique<effects::ModalEffectDefinition>(
                std::move(options));
        }
        if (type == "ChangeLandTypeEffect")
        {
            return std::make_unique<effects::ChangeLandTypeEffectDefinition>();
        }
        if (type == "MillEffect")
        {
            return std::make_unique<effects::MillEffectDefinition>(
                data.at("amount").get<int>(),
                dandan::core::TargetRequirement{target_types});
        }
        if (type == "ScryEffect")
        {
            return std::make_unique<effects::ScryEffectDefinition>(
                data.at("scry_amount").get<int>());
        }
        if (type == "PeekEffect")
        {
            return std::make_unique<effects::PeekEffectDefinition>(
                data.at("peek_amount").get<int>());
        }
        if (type == "DrawEffect")
        {
            try
            {
                auto number{data.at("amount").get<int>()};
                return std::make_unique<effects::DrawEffectDefinition>(number);
            }
            catch (const nlohmann::json::exception &e)
            {
                const auto &amount_json = data.at("amount");
                auto amount =
                    JsonFactory<numbers::INumber>::create_product(amount_json);
                return std::make_unique<effects::DrawEffectDefinition>(
                    std::move(amount));
            }
        }
        if (type == "BounceLandEffect")
        {
            return std::make_unique<effects::BounceLandEffectDefinition>();
        }
        if (type == "SelfSacrificeEffect")
        {
            return std::make_unique<effects::SelfSacrificeEffectDefinition>();
        }
        if (type == "PutCardOnTopEffect")
        {
            return std::make_unique<effects::PutCardOnTopEffectDefinition>(
                data.at("amount").get<int>());
        }
        if (type == "TimeTwisterEffect")
        {
            return std::make_unique<effects::TimeTwisterEffectDefinition>();
        }
        if (type == "ExileTopEffect")
        {
            return std::make_unique<effects::ExileTopEffectDefinition>(
                data.at("amount").get<int>());
        }
        if (type == "OptionalDrawEffect")
        {
            return std::make_unique<effects::OptionalDrawEffectDefinition>(
                data.at("amount").get<int>(),
                data.at("each_player").get<bool>());
        }
        if (type == "TutorTopEffect")
        {
            std::vector<core::CardData::Type> filter_types;
            std::transform(
                data.at("filter_types").begin(), data.at("filter_types").end(),
                std::back_inserter(filter_types), [](const auto &type_json)
                { return type_json.template get<core::CardData::Type>(); });
            // for (const auto &type_json : data.at("filter_types"))
            // {
            //     filter_types.push_back(type_json.get<core::CardData::Type>());
            // }
            return std::make_unique<effects::TutorTopEffectDefinition>(
                std::move(filter_types));
        }
        if (type == "MindBendEffect")
        {
            // TODO: add expiry option to other locations as well
            auto effect{std::make_unique<effects::MindBendEffectDefinition>(
                core::TargetRequirement{target_types})};
            effect->addExpireTime(expiry);
            return effect;
        }
        if (type == "BounceEffect")
        {
            return std::make_unique<effects::BounceEffectDefinition>(
                core::TargetRequirement{target_types});
        }
        if (type == "MemoryLapseEffect")
        {

            return std::make_unique<effects::MemoryLapseEffectDefinition>(
                core::TargetRequirement{target_types});
        }
        if (type == "ChooseCardNameAndMillEffect")
        {
            return std::make_unique<
                effects::ChooseCardNameAndMillEffectDefinition>(
                data.at("amount").get<int>(),
                core::TargetRequirement{target_types});
        }

        throw std::runtime_error("Unknown effect type: " + type);
    }
} // namespace dandan::serialization
#endif // DANDAN_SERIALIZE