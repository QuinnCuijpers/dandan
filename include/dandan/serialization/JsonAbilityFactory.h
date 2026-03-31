#ifndef DANDAN_JSONABILITYFACTORY_H
#define DANDAN_JSONABILITYFACTORY_H

#include "dandan/abilities/IAbility.h"
#include "JsonFactory.h"
#include <nlohmann/json_fwd.hpp>

namespace dandan::serialization
{
    template <>
    class JsonFactory<abilities::IAbility>
    {
    public:
        static nlohmann::json create_json(const abilities::IAbility *ability);

        static std::unique_ptr<abilities::IAbility> create_product(const nlohmann::json &j);
    };
}

#endif