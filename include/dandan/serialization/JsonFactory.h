#ifndef DANDAN_JSONFACTORY_H
#define DANDAN_JSONFACTORY_H

#ifdef DANDAN_BUILD_SERIALIZE

#include <memory>
#include <nlohmann/json_fwd.hpp>

namespace dandan::serialization
{
    template <typename T> class JsonFactory
    {
    public:
        static nlohmann::json create_json(const T *obj);

        static std::unique_ptr<T> create_product(const nlohmann::json &j);
    };
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE

#endif // DANDAN_JSONFACTORY_H