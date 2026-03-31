#ifndef DANDAN_JSONREPLACEFACTORY_H
#define DANDAN_JSONREPLACEFACTORY_H
#include "JsonFactory.h"
#include "dandan/effects/IReplacementEffect.h"

namespace dandan::serialization
{
    template <>
    class JsonFactory<effects::IReplacementEffect>
    {
    public:
        static nlohmann::json create_json(const effects::IReplacementEffect *obj);

        static std::unique_ptr<effects::IReplacementEffect> create_product(const nlohmann::json &j);
    };
}

#endif