#ifndef DANDAN_BOARD_H
#define DANDAN_BOARD_H

#include "Card.h"
#include "dandan/core/CardTypes.h"

#include <map>
#include <vector>

namespace dandan::core
{

    class Game;

    using Permanent = CardID;
    using PermanentMap = std::map<core::Type, std::vector<Permanent>>;

    // TODO: expand docs
    /** @brief A class representing the battlefield.
     * @class Battlefield
     */
    class Battlefield
    {
    public:
        /** Add a card to the battlefield.
         * @param card The card to add.
         */
        void addCard(Card &card);

        /** Get the permanents on the battlefield mutably.
         * @return A reference to the permanents map.
         */
        [[nodiscard]] PermanentMap &permanents();

        /** Get the permanents on the battlefield immutably.
         * @return A const reference to the permanents map.
         */
        [[nodiscard]] const PermanentMap &permanents() const;

        /** Get the lands on the battlefield.
         * @return A const reference to the lands vector.
         */
        [[nodiscard]] const std::vector<Permanent> &getLands() const;

        /** Get the creatures on the battlefield.
         * @return A const reference to the creatures vector.
         */
        [[nodiscard]] const std::vector<Permanent> &getCreatures() const;

        /** Get a land from the battlefield, the land is removed from the
         * battlefield.
         * @param card_index The index of the land to get.
         * @return The land at the specified index.
         */
        [[nodiscard]] Permanent getLand(int card_index);

        /** Remove a card from the battlefield.
         * @param card The card to remove.
         */
        void removeCard(const Card &card);

        void sacrificeCard(Card &card, core::Game &game);

    private:
        PermanentMap m_permanents{{Type::Land, {}},        {Type::Creature, {}},
                                  {Type::Sorcery, {}},     {Type::Instant, {}},
                                  {Type::Enchantment, {}}, {Type::Artifact, {}},
                                  {Type::Planeswalker, {}}};
    };
}; // namespace dandan::core

#endif
