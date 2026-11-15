#ifndef DANDAN_CARDREGISTRY_H
#define DANDAN_CARDREGISTRY_H

#include "dandan/core/CardID.h"
#include <filesystem>
#include <map>
#include <memory>
#include <optional>
#include <vector>

namespace dandan::core
{
    class Card;

    /** @brief Owns the card instances used by a game and provides ID lookup.
     * @class CardRegistry
     */
    class CardRegistry
    {
    public:
        CardRegistry() = default;

#ifdef DANDAN_SERIALIZE
        void load_cards(const std::filesystem::path &path);
#endif

        /** Constructs a registry and optionally loads cards from a decklist.
         * @param path The decklist to load, or std::nullopt for no cards.
         */
        explicit CardRegistry(std::optional<std::filesystem::path> path);

        /** Gets the IDs of all registered cards.
         * @return A vector containing every registered card ID.
         */
        [[nodiscard]] std::vector<CardID> card_ids() const;

        /** Replaces the registered cards.
         * @param cards The cards to register.
         */
        void setCards(std::vector<Card> cards);

        /** Looks up a card by ID.
         * @param card_id The ID of the card to find.
         * @return A pointer to the card, or nullptr if it is not registered.
         */
        Card *get(CardID card_id);

        /** Looks up a card by its integer ID.
         * @param card_id The integer ID of the card to find.
         * @return A pointer to the card, or nullptr if it is not registered.
         */
        Card *get(int card_id);

        /** Looks up a card by ID.
         * @param card_id The ID of the card to find.
         * @return A pointer to the card, or nullptr if it is not registered.
         */
        [[nodiscard]] Card *get(CardID card_id) const;

        /** Looks up a card by its integer ID.
         * @param card_id The integer ID of the card to find.
         * @return A pointer to the card, or nullptr if it is not registered.
         */
        [[nodiscard]] Card *get(int card_id) const;

        /** Looks up a card by ID.
         * @param card_id The ID of the card to find.
         * @return A pointer to the card, or nullptr if it is not registered.
         */
        Card *operator[](CardID card_id);

        /** Looks up a card by its integer ID.
         * @param card_id The integer ID of the card to find.
         * @return A pointer to the card, or nullptr if it is not registered.
         */
        Card *operator[](int card_id);

        /** Looks up a card by ID.
         * @param card_id The ID of the card to find.
         * @return A pointer to the card, or nullptr if it is not registered.
         */
        const Card *operator[](CardID card_id) const;

        /** Looks up a card by its integer ID.
         * @param card_id The integer ID of the card to find.
         * @return A pointer to the card, or nullptr if it is not registered.
         */
        const Card *operator[](int card_id) const;

    private:
        std::map<CardID, std::unique_ptr<Card>> m_card_lookup;
        std::optional<std::filesystem::path> m_decklist_path;
    };
} // namespace dandan::core
#endif
