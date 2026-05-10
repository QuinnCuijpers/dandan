#ifndef DANDAN_CARDFACTORY_H
#define DANDAN_CARDFACTORY_H

#ifdef DANDAN_BUILD_SERIALIZE

#include "dandan/core/CardData.h"
#include "dandan/serialization/JsonFactory.h"

namespace dandan::serialization
{

    template <> class JsonFactory<core::CardData>
    {
    public:
        static nlohmann::json create_json(const core::CardData *card);

        static std::unique_ptr<core::CardData> create_product(
            const nlohmann::json &json);
    };
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE

#endif // DANDAN_CARDFACTORY_H