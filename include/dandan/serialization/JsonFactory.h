#ifndef DANDAN_JSONFACTORY_H
#define DANDAN_JSONFACTORY_H

#include <nlohmann/json_fwd.hpp>
#include <memory>

namespace dandan::serialization
{
    template <typename T> class JsonFactory
    {
    public:
        static nlohmann::json create_json(const T *obj);

        static std::unique_ptr<T> create_product(const nlohmann::json &j);
    };
} // namespace dandan::serialization

#endif