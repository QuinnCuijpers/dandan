#ifndef DANDAN_JSONFACTORY_H
#define DANDAN_JSONFACTORY_H

#include "dandan/mana/ManaList.h"
#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonTypeRegistry.h"
#include <memory>
#include <nlohmann/json.hpp>

namespace dandan::serialization::impl
{
    template <typename T, typename = void>
    struct has_type_registry : std::false_type
    {
    };

    template <typename T>
    struct has_type_registry<
        T, std::void_t<decltype(JsonTypeRegistry<T>::instance())>>
        : std::true_type
    {
    };
} // namespace dandan::serialization::impl

namespace dandan::serialization
{
    template <typename T> class JsonFactory
    {
        static_assert(
            impl::has_type_registry<T>::value,
            "JsonFactory<T>: no JsonTypeRegistry<T> found. Register T with "
            "JsonTypeRegistry, or add a full specialization JsonFactory<T> "
            "for concrete (non-polymorphic) types.");

    public:
        static nlohmann::json create_json(const T *obj)
        {
            if (obj == nullptr)
            {
                throw std::invalid_argument(
                    "JsonFactory<T>::create_json: obj must not be null");
            }
            auto json = nlohmann::json::object();
            const auto &registration{
                JsonTypeRegistry<T>::instance().serializerFor(*obj)};

            auto data = registration.serializer(obj);

            if (registration.representation == JsonRepresentation::INLINE)
            {
                return data;
            }

            json["type"] = registration.name;
            json["data"] = data;

            return json;
        }

        static std::unique_ptr<T> create_product(const nlohmann::json &json)
        {
            const auto &type = json.at("type").get<std::string>();
            return JsonTypeRegistry<T>::instance().deserializerFor(type)(
                json.at("data"));
        }
    };

    template <> class JsonFactory<dandan::mana::ManaList>
    {
    public:
        static nlohmann::json create_json(const dandan::mana::ManaList &mana);

        static dandan::mana::ManaList create_product(
            const nlohmann::json &json);
    };

    template <> class JsonFactory<dandan::mana::ManaPrice>
    {
    public:
        static nlohmann::json create_json(const dandan::mana::ManaPrice *mana);
        static dandan::mana::ManaPrice create_product(
            const nlohmann::json &json);
    };

    template <> class JsonFactory<dandan::mana::ManaBag>
    {
    public:
        static nlohmann::json create_json(const dandan::mana::ManaBag *mana);
        static dandan::mana::ManaBag create_product(const nlohmann::json &json);
    };

    template <> class JsonFactory<effects::IOneShotEffectDefinition>
    {
    public:
        static nlohmann::json create_json(
            const effects::IOneShotEffectDefinition *effect);

        static std::unique_ptr<effects::IOneShotEffectDefinition>
        create_product(const nlohmann::json &json);
    };

    template <> class JsonFactory<core::CardData>
    {
    public:
        static nlohmann::json create_json(const core::CardData *card);

        static std::unique_ptr<core::CardData> create_product(
            const nlohmann::json &json);
    };
} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE

#endif // DANDAN_JSONFACTORY_H
