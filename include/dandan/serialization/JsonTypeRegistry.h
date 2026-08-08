#ifndef DANDAN_JSONTYPEREGISTRY_H
#define DANDAN_JSONTYPEREGISTRY_H

#include "dandan/conditions/ICondition.h"
#include "dandan/numbers/INumber.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <string_view>
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

        static JsonTypeRegistry &instance()
        {
            static JsonTypeRegistry registry{};
            return registry;
        }

        void registerType(
            std::string name, std::type_index type, Serializer serializer,
            Deserializer deserializer,
            JsonRepresentation representation = JsonRepresentation::TAGGED)
        {
            m_serializer_map[type] = {name, std::move(serializer),
                                      representation};
            m_deserializer_map[name] = std::move(deserializer);
        }

        Deserializer deserializerFor(const std::string &name)
        {
            return m_deserializer_map.at(name);
        }

        JsonRegistration &serializerFor(const Product &obj)
        {
            return m_serializer_map.at(std::type_index(typeid(obj)));
        }

        bool contains(std::string_view name)
        {
            return m_deserializer_map.count(name) > 0;
        }

    private:
        std::unordered_map<std::type_index, JsonRegistration> m_serializer_map;
        std::unordered_map<std::string, Deserializer> m_deserializer_map;
    };

    using NumberRegistry = JsonTypeRegistry<numbers::INumber>;
    using ConditionRegistry = JsonTypeRegistry<conditions::ICondition>;
} // namespace dandan::serialization

#endif
