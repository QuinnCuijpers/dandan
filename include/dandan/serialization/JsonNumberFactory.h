
#ifndef DANDAN_JSONNUMBERFACTORY_H
#define DANDAN_JSONNUMBERFACTORY_H

#ifdef DANDAN_SERIALIZE

#include "JsonFactory.h"
#include "dandan/numbers/INumber.h"
#include <nlohmann/json_fwd.hpp>

namespace dandan::serialization
{
    template <> class JsonFactory<numbers::INumber>
    {
    public:
        static nlohmann::json create_json(const numbers::INumber *number);

        static std::unique_ptr<numbers::INumber> create_product(
            const nlohmann::json &json);
    };
} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE

#endif // DANDAN_JSONCOSTFACTORY_H