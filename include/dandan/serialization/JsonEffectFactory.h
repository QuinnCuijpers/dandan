#ifndef DANDAN_JSONEFFECTFACTORY_H
#define DANDAN_JSONEFFECTFACTORY_H

#ifdef DANDAN_BUILD_SERIALIZE

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
            const nlohmann::json &json);
    };
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE

#endif // DANDAN_JSONEFFECTFACTORY_H