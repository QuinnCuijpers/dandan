#ifndef DANDAN_CARDFACTORY_H
#define DANDAN_CARDFACTORY_H

#ifdef DANDAN_BUILD_SERIALIZE

#include "dandan/core/Card.h"
#include "dandan/serialization/JsonFactory.h"

namespace dandan::serialization
{

    template <> class JsonFactory<core::Card>
    {
    public:
        static nlohmann::json create_json(const core::Card *card);

        static std::unique_ptr<core::Card> create_product(
            const nlohmann::json &json);
    };
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE

#endif // DANDAN_CARDFACTORY_H