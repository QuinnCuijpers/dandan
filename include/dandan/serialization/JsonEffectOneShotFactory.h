#ifndef DANDAN_JSONEFFECTFACTORY_H
#define DANDAN_JSONEFFECTFACTORY_H

#ifdef DANDAN_SERIALIZE
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

#include "JsonFactory.h"
#include <nlohmann/json_fwd.hpp>

namespace dandan::serialization
{
    template <> class JsonFactory<effects::IOneShotEffectDefinition>
    {
    public:
        static nlohmann::json create_json(
            const effects::IOneShotEffectDefinition *effect);

        static std::unique_ptr<effects::IOneShotEffectDefinition>
        create_product(const nlohmann::json &json);
    };
} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE

#endif // DANDAN_JSONEFFECTFACTORY_H