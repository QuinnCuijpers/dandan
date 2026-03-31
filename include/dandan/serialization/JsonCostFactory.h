#ifndef DANDAN_JSONCOSTFACTORY_H
#define DANDAN_JSONCOSTFACTORY_H

#include "JsonFactory.h"
#include "dandan/costs/ICost.h"
#include <nlohmann/json_fwd.hpp>

namespace dandan::serialization
{
    template <>
    class JsonFactory<costs::ICost>
    {
    public:
        static nlohmann::json create_json(const costs::ICost *cost);

        static std::unique_ptr<costs::ICost> create_product(const nlohmann::json &j);
    };
}

#endif