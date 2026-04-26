#ifndef DANDAN_JSONEFFECTCONTINUOUSFACTORY_H
#define DANDAN_JSONEFFECTCONTINUOUSFACTORY_H

#ifdef DANDAN_BUILD_SERIALIZE
#include "JsonFactory.h"
#include "dandan/effects/continuous/IContinuousEffect.h"

namespace dandan::serialization
{
    template <> class JsonFactory<effects::IContinuousEffect>
    {
    public:
        static nlohmann::json create_json(
            const effects::IContinuousEffect *effect);

        static std::unique_ptr<effects::IContinuousEffect> create_product(
            const nlohmann::json &json);
    };
} // namespace dandan::serialization
#endif // DANDAN_BUILD_SERIALIZE

#endif // DANDAN_JSONEFFECTCONTINUOUSFACTORY_H