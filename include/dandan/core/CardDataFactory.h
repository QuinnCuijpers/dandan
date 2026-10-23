#ifndef DANDAN_CARDDATAFACTORY_H
#define DANDAN_CARDDATAFACTORY_H

#include "dandan/abilities/BasicLandAbility.h"
#include "dandan/core/CardData.h"
#include <memory>
#include <stdexcept>
#include <unordered_map>

#ifdef DANDAN_SERIALIZE
#include <string_view>
#endif

namespace dandan::core
{
    /** @brief A caching factory for creating CardData instances keyed by name.
     * @class CardDataFactory
     */
    class CardDataFactory
    {
    public:
#ifdef DANDAN_SERIALIZE
        static const CardData &createCardData(std::string_view name);
#endif

    private:
        static std::unordered_map<std::string, std::unique_ptr<CardData>>
            m_card_data_cache;
    };
} // namespace dandan::core

#endif // DANDAN_CARDDATAFACTORY_H
