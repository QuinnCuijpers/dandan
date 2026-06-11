#include "dandan/serialization/JsonEffectOneShotFactory.h"
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
#include "dandan/serialization/JsonEnums.h" //IWYU pragma: keep
#include "nlohmann/json_fwd.hpp"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<effects::IOneShotEffectDefinition>::create_json(
        const effects::IOneShotEffectDefinition *effect)
    {

        if (const auto *ModalEffect =
                dynamic_cast<const effects::ModalEffectDefinition *>(effect))
        {
            auto json = nlohmann::json{{"type", "ModalEffect"},
                                       {"data", nlohmann::json::object()}};
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
            auto json = nlohmann::json{{"type", "ScryEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["scry_amount"] = scryEffect->getScryAmount();
            return json;
        }
        if (const auto *peekEffect =
                dynamic_cast<const effects::PeekEffectDefinition *>(effect))
        {
            auto json = nlohmann::json{{"type", "PeekEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["peek_amount"] = peekEffect->getPeekAmount();
            return json;
        }
        if (const auto *drawEffect =
                dynamic_cast<const effects::DrawEffectDefinition *>(effect))
        {
            auto json = nlohmann::json{{"type", "DrawEffect"},
                                       {"data", nlohmann::json::object()}};
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
            auto json = nlohmann::json{{"type", "BounceLandEffect"},
                                       {"data", nlohmann::json::object()}};
            return json;
        }
        if (dynamic_cast<const effects::SelfSacrificeEffectDefinition *>(
                effect) != nullptr)
        {
            auto json = nlohmann::json{{"type", "SelfSacrificeEffect"},
                                       {"data", nlohmann::json::object()}};
            return json;
        }
        if (const auto *putCardOnTopEffect =
                dynamic_cast<const effects::PutCardOnTopEffectDefinition *>(
                    effect))
        {
            auto json = nlohmann::json{{"type", "PutCardOnTopEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["amount"] = putCardOnTopEffect->getAmount();
            return json;
        }

        if (dynamic_cast<const effects::TimeTwisterEffect *>(effect) != nullptr)
        {
            auto json = nlohmann::json{{"type", "TimeTwisterEffect"},
                                       {"data", nlohmann::json::object()}};
            return json;
        }

        if (const auto *exileTopEffect =
                dynamic_cast<const effects::ExileTopEffectDefinition *>(effect))
        {
            auto json = nlohmann::json{{"type", "ExileTopEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["amount"] = exileTopEffect->getAmount();
            return json;
        }

        if ([[maybe_unused]] const auto *optionalDrawEffect =
                dynamic_cast<const effects::OptionalDrawEffectDefinition *>(
                    effect))
        {
            auto json = nlohmann::json{{"type", "OptionalDrawEffect"},
                                       {"data", nlohmann::json::object()}};

            json["data"]["amount"] = optionalDrawEffect->getAmount();
            json["data"]["each_player"] = optionalDrawEffect->isEachPlayer();
            return json;
        }

        if (const auto *tutorTopEffect =
                dynamic_cast<const effects::TutorTopEffectDefinition *>(effect))
        {
            auto json = nlohmann::json{{"type", "TutorTopEffect"},
                                       {"data", nlohmann::json::object()}};
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
            auto json = nlohmann::json{{"type", "MillEffect"},
                                       {"data", nlohmann::json::object()}};
            json["data"]["amount"] = millEffect->getAmount();
            return json;
        }

        if (dynamic_cast<const effects::ChangeLandTypeEffectDefinition *>(
                effect) != nullptr)
        {
            auto json = nlohmann::json{{"type", "ChangeLandTypeEffect"},
                                       {"data", nlohmann::json::object()}};
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
        const auto &type = json.at("type").get<std::string>();
        const auto &data = json.at("data");

        if (type == "ModalEffect")
        {
            std::vector<std::unique_ptr<effects::IOneShotEffectDefinition>>
                options;
            for (const auto &option_json : data.at("options"))
            {
                options.push_back(create_product(option_json));
            }
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
                data.at("amount").get<int>());
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
            return std::make_unique<effects::TimeTwisterEffect>();
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
            for (const auto &type_json : data.at("filter_types"))
            {
                filter_types.push_back(type_json.get<core::CardData::Type>());
            }
            return std::make_unique<effects::TutorTopEffectDefinition>(
                std::move(filter_types));
        }
        throw std::runtime_error("Unknown effect type: " + type);
    }
} // namespace dandan::serialization
#endif // DANDAN_SERIALIZE