#ifndef DANDAN_JSONFACTORY_H
#define DANDAN_JSONFACTORY_H

#include <memory>
#include <nlohmann/json_fwd.hpp>

// TODO: consider using subtype polymorphism instead of template specialization
// for each type
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