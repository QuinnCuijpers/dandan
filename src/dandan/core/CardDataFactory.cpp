#include "dandan/core/CardDataFactory.h"
#include <memory>

namespace dandan::core
{
    std::unordered_map<std::string, std::unique_ptr<CardData>>
        CardDataFactory::m_card_data_cache;

#ifdef DANDAN_SERIALIZE
    const CardData &CardDataFactory::createCardData(std::string_view name)
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
            auto ptr{
                std::make_unique<CardData>(std::move(new_card_data.value()))};
            if (ptr->supertype == core::SuperType::Basic)
            {
                ptr->abilities.push_back(
                    std::make_unique<abilities::BasicLandAbility>());
            }
            const auto &ref = *ptr;
            m_card_data_cache[key] = std::move(ptr);
            return ref;
        }

        throw std::runtime_error("No CardData found for card with this name: " +
                                 std::string{name});
    }
#endif
} // namespace dandan::core
