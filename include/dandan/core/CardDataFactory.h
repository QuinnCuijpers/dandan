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
        static const CardData &createCardData(const std::string_view name)
        {
            std::string key{name};
            if (auto iter = m_card_data_cache.find(key);
                iter != m_card_data_cache.end())
            {
                return *(iter->second);
            }

            auto new_card_data{getCardData(name)};
            if (new_card_data.has_value())
            {
                auto ptr{std::make_unique<CardData>(
                    std::move(new_card_data.value()))};
                if (ptr->supertype == core::SuperType::Basic)
                {
                    ptr->abilities.push_back(
                        std::make_unique<abilities::BasicLandAbility>());
                }
                const auto &ref = *ptr;
                m_card_data_cache[key] = std::move(ptr);
                return ref;
            }

            throw std::runtime_error(
                "No CardData found for card with this name: " +
                std::string{name});
        }
#endif

    private:
        static std::unordered_map<std::string, std::unique_ptr<CardData>>
            m_card_data_cache;
    };
} // namespace dandan::core

#endif // DANDAN_CARDDATAFACTORY_H
