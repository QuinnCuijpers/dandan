#ifndef DANDAN_CARDDATAFACTORY_H
#define DANDAN_CARDDATAFACTORY_H

#include "dandan/core/CardData.h"
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
        static CardData &createCardData(const std::string_view name)
        {
            std::string key{name};
            if (auto iter = m_card_data_cache.find(key);
                iter != m_card_data_cache.end())
            {
                return iter->second;
            }
            CardData new_card_data{name};
            m_card_data_cache[key] = std::move(new_card_data);
            return m_card_data_cache[key];
        }
#endif

    private:
        static std::unordered_map<std::string, CardData> m_card_data_cache;
    };
} // namespace dandan::core

#endif // DANDAN_CARDDATAFACTORY_H
