#ifndef DANDAN_JSONCONDITIONFACTORY_H
#define DANDAN_JSONCONDITIONFACTORY_H

#ifdef DANDAN_BUILD_SERIALIZE
#include "JsonFactory.h"
#include "dandan/conditions/ICondition.h"

namespace dandan::serialization
{
    template <> class JsonFactory<conditions::ICondition>
    {
    public:
        static nlohmann::json create_json(
            [[maybe_unused]] const conditions::ICondition *condition);

        static std::unique_ptr<conditions::ICondition> create_product(
            [[maybe_unused]] const nlohmann::json &json);
    };
} // namespace dandan::serialization
#endif
#endif