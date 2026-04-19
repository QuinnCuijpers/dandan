#ifndef DANDAN_JSONMANAFACTORY_H
#define DANDAN_JSONMANAFACTORY_H

#include "dandan/mana/ManaList.h"
#include "dandan/serialization/JsonFactory.h"

namespace dandan::serialization
{
    template <> class JsonFactory<dandan::mana::ManaList>
    {
    public:
        static nlohmann::json create_json(const dandan::mana::ManaList *mana);

        static std::unique_ptr<dandan::mana::ManaList> create_product(
            const nlohmann::json &j);
    };

    template <> class JsonFactory<dandan::mana::Mana>
    {
    public:
        static nlohmann::json create_json(const dandan::mana::Mana &mana);
        static std::unique_ptr<dandan::mana::Mana> create_product(
            const nlohmann::json &j);
    };
} // namespace dandan::serialization

#endif // DANDAN_JSONMANAFACTORY_H