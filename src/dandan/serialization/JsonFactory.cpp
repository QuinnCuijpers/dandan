#include "dandan/serialization/JsonFactory.h"
#include <nlohmann/json.hpp>
#include <stdexcept>

namespace dandan::serialization
{
    template <typename T>
    std::unique_ptr<T> JsonFactory<T>::create_product(
        [[maybe_unused]] const nlohmann::json &j)
    {
        throw std::logic_error("JsonFactory not implemented for this type");
    }

    template <typename T>
    nlohmann::json JsonFactory<T>::create_json([[maybe_unused]] const T *obj)
    {
        throw std::logic_error("JsonFactory not implemented for this type");
    }
} // namespace dandan::serialization