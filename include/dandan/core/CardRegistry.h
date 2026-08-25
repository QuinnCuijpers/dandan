#ifndef DANDAN_CARDREGISTRY_H
#define DANDAN_CARDREGISTRY_H

#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include <filesystem>
#include <optional>
#include <unordered_map>
#include <vector>

namespace dandan::core
{

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

        void setCards(const std::vector<Card> &cards);

        Card &operator[](CardID card_id);

        Card &operator[](int card_id);

    private:
        std::unordered_map<CardID, Card> m_card_lookup;
        std::optional<std::filesystem::path> m_decklist_path;
    };
} // namespace dandan::core
#endif
