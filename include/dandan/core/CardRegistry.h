#ifndef DANDAN_CARDREGISTRY_H
#define DANDAN_CARDREGISTRY_H

#include "dandan/core/CardID.h"
#include <filesystem>
#include <map>
#include <optional>
#include <vector>

namespace dandan::core
{
    class Card;

    class CardRegistry
    {
    public:
        CardRegistry() = default;

#ifdef DANDAN_SERIALIZE
        void load_cards(const std::filesystem::path &path);
#endif

        explicit CardRegistry(std::optional<std::filesystem::path> path);

        [[nodiscard]] std::vector<CardID> card_ids() const;

        void setCards(std::vector<Card> cards);

        Card *operator[](CardID card_id);

        Card *operator[](int card_id);

        const Card *operator[](CardID card_id) const;

        const Card *operator[](int card_id) const;

    private:
        std::map<CardID, Card> m_card_lookup;
        std::optional<std::filesystem::path> m_decklist_path;
    };
} // namespace dandan::core
#endif
