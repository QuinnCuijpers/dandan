#ifndef DANDAN_CARDREGISTRY_H
#define DANDAN_CARDREGISTRY_H

#include "dandan/core/CardID.h"
#include <deque>
#include <filesystem>
#include <optional>
#include <unordered_map>
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

        std::vector<CardID> card_ids() const;

        std::vector<Card *> cards() const;

        void setCards(std::deque<Card> cards);

        Card *operator[](CardID card_id) const;

        Card *operator[](int card_id) const;

    private:
        std::deque<Card> m_cards;
        std::unordered_map<CardID, Card *> m_card_lookup;
        std::optional<std::filesystem::path> m_decklist_path;
    };
} // namespace dandan::core
#endif
