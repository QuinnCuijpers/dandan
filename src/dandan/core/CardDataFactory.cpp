#include "dandan/core/CardDataFactory.h"
#include <memory>

namespace dandan::core
{
    std::unordered_map<std::string, std::unique_ptr<CardData>>
        CardDataFactory::m_card_data_cache;
} // namespace dandan::core
