#ifndef DANDAN_JSONEFFECTFACTORY_H
#define DANDAN_JSONEFFECTFACTORY_H

#ifdef DANDAN_BUILD_SERIALIZE

#include "JsonFactory.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <nlohmann/json_fwd.hpp>

namespace dandan::serialization
{
    template <> class JsonFactory<effects::IOneShotEffect>
    {
    public:
        static nlohmann::json create_json(
            const effects::IOneShotEffect *effect);

        static std::unique_ptr<effects::IOneShotEffect> create_product(
            const nlohmann::json &json);
    };
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE

#endif // DANDAN_JSONEFFECTFACTORY_H