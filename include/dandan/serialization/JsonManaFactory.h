#ifndef DANDAN_JSONMANAFACTORY_H
#define DANDAN_JSONMANAFACTORY_H

#include "dandan/mana/ManaBag.h"
#include "dandan/mana/ManaPrice.h"
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

    template <> class JsonFactory<dandan::mana::ManaPrice>
    {
    public:
        static nlohmann::json create_json(const dandan::mana::ManaPrice *mana);
        static dandan::mana::ManaPrice create_product(
            const nlohmann::json &json);
    };

    template <> class JsonFactory<dandan::mana::ManaBag>
    {
    public:
        static nlohmann::json create_json(const dandan::mana::ManaBag *mana);
        static dandan::mana::ManaBag create_product(const nlohmann::json &json);
    };
} // namespace dandan::serialization

#endif // DANDAN_JSONMANAFACTORY_H
#endif // DANDAN_SERIALIZE
