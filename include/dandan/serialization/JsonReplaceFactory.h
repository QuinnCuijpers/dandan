#ifndef DANDAN_JSONREPLACEFACTORY_H
#define DANDAN_JSONREPLACEFACTORY_H
#include "JsonFactory.h"
#include "dandan/replacement_effects/IReplacementEffect.h"

namespace dandan::serialization
{
    template <> class JsonFactory<replacement_effects::IReplacementEffect>
    {
    public:
        static nlohmann::json create_json(
            const replacement_effects::IReplacementEffect *obj);

        static std::unique_ptr<replacement_effects::IReplacementEffect>
        create_product(const nlohmann::json &j);
    };
} // namespace dandan::serialization

#endif