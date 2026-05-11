#ifndef DANDAN_JSONTRIGGERFACTORY_H
#define DANDAN_JSONTRIGGERFACTORY_H

#ifdef DANDAN_BUILD_SERIALIZE

#include "JsonFactory.h"
#include "dandan/triggers/ITrigger.h"

namespace dandan::serialization
{
    template <> class JsonFactory<triggers::ITrigger>
    {
    public:
        static std::unique_ptr<dandan::triggers::ITrigger> create_product(
            const nlohmann::json &json,
            core::CardID card_id = core::CardID::getInvalidID());

        static std::unique_ptr<dandan::triggers::ITrigger> create_product(
            const nlohmann::json &json);

        static nlohmann::json create_json(
            const dandan::triggers::ITrigger *trigger);
    };
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE

#endif // DANDAN_JSONTRIGGERFACTORY_H