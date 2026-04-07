#ifndef DANDAN_JSONEFFECTFACTORY_H
#define DANDAN_JSONEFFECTFACTORY_H

#include "JsonFactory.h"
#include "dandan/effects/IEffect.h"
#include <nlohmann/json_fwd.hpp>

namespace dandan::serialization
{
    template <> class JsonFactory<effects::IEffect>
    {
    public:
        static nlohmann::json create_json(const effects::IEffect *effect);

        static std::unique_ptr<effects::IEffect> create_product(
            const nlohmann::json &j);
    };
} // namespace dandan::serialization

#endif