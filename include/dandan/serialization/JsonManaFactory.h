#ifndef DANDAN_JSONMANAFACTORY_H
#define DANDAN_JSONMANAFACTORY_H

#ifdef DANDAN_SERIALIZE

#include "dandan/mana/ManaList.h"
#include "dandan/serialization/JsonFactory.h"

namespace dandan::serialization
{
    template <> class JsonFactory<dandan::mana::ManaList>
    {
    public:
        static nlohmann::json create_json(const dandan::mana::ManaList *mana);

        static std::unique_ptr<dandan::mana::ManaList> create_product(
            const nlohmann::json &json);
    };

    template <> class JsonFactory<dandan::mana::Manapool>
    {
    public:
        static nlohmann::json create_json(const dandan::mana::Manapool *mana);
        static std::unique_ptr<dandan::mana::Manapool> create_product(
            const nlohmann::json &json);
    };
} // namespace dandan::serialization

#endif // DANDAN_JSONMANAFACTORY_H
#endif // DANDAN_SERIALIZE
