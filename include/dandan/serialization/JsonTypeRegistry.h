#ifndef DANDAN_JSONTYPEREGISTRY_H
#define DANDAN_JSONTYPEREGISTRY_H

#ifdef DANDAN_SERIALIZE

#include "dandan/conditions/ICondition.h"
#include "dandan/numbers/INumber.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <utility>

namespace dandan::serialization
{
    enum class JsonRepresentation : std::uint8_t
    {
        TAGGED,
        INLINE
    };

    template <typename Product, typename... Args> class JsonTypeRegistry
    {
    public:
        using Deserializer = std::function<std::unique_ptr<Product>(
            const nlohmann::json &, Args...)>;
        using Serializer = std::function<nlohmann::json(const Product *)>;

        struct JsonRegistration
        {
            std::string name;
            Serializer serializer;
            JsonRepresentation representation{JsonRepresentation::TAGGED};
        };

        JsonTypeRegistry &operator=(const JsonTypeRegistry &) = delete;
        JsonTypeRegistry &operator=(JsonTypeRegistry &&) = delete;
        JsonTypeRegistry(const JsonTypeRegistry &other) = delete;
        JsonTypeRegistry(JsonTypeRegistry &&other) = delete;
        ~JsonTypeRegistry() = default;

        static JsonTypeRegistry &instance()
        {
            static JsonTypeRegistry registry{};
            return registry;
        }

        template <typename T>
        void registerType(
            const std::string &type_name, Serializer serializer,
            Deserializer deserializer,
            JsonRepresentation representation = JsonRepresentation::TAGGED)
        {
            static_assert(std::is_base_of_v<Product, T>);
            m_serializer_map[std::type_index(typeid(T))] = {
                type_name, std::move(serializer), representation};
            m_deserializer_map[type_name] = std::move(deserializer);
        }

        Deserializer deserializerFor(const std::string &name)
        {
            std::cout << name << '\n';
            return m_deserializer_map.at(name);
        }

        JsonRegistration &serializerFor(const Product &obj)
        {
            std::cout << typeid(obj).name() << '\n';
            try
            {
                return m_serializer_map.at(std::type_index(typeid(obj)));
            }
            catch (const std::exception &e)
            {
                std::cout << "Couldn't find serializer for "
                          << typeid(obj).name() << '\n';
                std::cout << e.what() << '\n';
                throw e;
            }
        }

        [[nodiscard]] bool contains(const std::string &name) const
        {
            return m_deserializer_map.count(name) > 0;
        }

    private:
        std::unordered_map<std::type_index, JsonRegistration> m_serializer_map;
        std::unordered_map<std::string, Deserializer> m_deserializer_map;

        JsonTypeRegistry() = default;
    };

    using NumberRegistry = JsonTypeRegistry<numbers::INumber>;
    using ConditionRegistry = JsonTypeRegistry<conditions::ICondition>;
} // namespace dandan::serialization

#endif
#endif
