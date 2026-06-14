#ifndef DANDAN_BOARD_H
#define DANDAN_BOARD_H

#include "Card.h"
#include "dandan/core/CardData.h"
#include <algorithm>
#include <map>
#include <vector>

namespace dandan::core
{

    class Game;

    using Permanent = CardID;
    using PermanentMap = std::map<CardData::Type, std::vector<Permanent>>;

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
        void addCard(Card &card)
        {
            card.setZone(Zone::BATTLEFIELD);
            m_permanents[card.getData().getType()].emplace_back(card.getID());
        }

        /** Get the permanents on the battlefield mutably.
         * @return A reference to the permanents map.
         */
        [[nodiscard]] PermanentMap &permanents()
        {
            return m_permanents;
        }

        /** Get the permanents on the battlefield immutably.
         * @return A const reference to the permanents map.
         */
        [[nodiscard]] const PermanentMap &permanents() const
        {
            return m_permanents;
        }

        /** Get the lands on the battlefield.
         * @return A const reference to the lands vector.
         */
        [[nodiscard]] const std::vector<Permanent> &getLands() const
        {
            return m_permanents.at(CardData::Type::Land);
        }

        /** Get the creatures on the battlefield.
         * @return A const reference to the creatures vector.
         */
        [[nodiscard]] const std::vector<Permanent> &getCreatures() const
        {
            return m_permanents.at(CardData::Type::Creature);
        }

        /** Get a land from the battlefield, the land is removed from the
         * battlefield.
         * @param card_index The index of the land to get.
         * @return The land at the specified index.
         */
        [[nodiscard]] Permanent getLand(int card_index)
        {
            auto &vec = m_permanents.at(CardData::Type::Land);
            auto card = vec[card_index];
            vec.erase(vec.begin() + card_index);
            return card;
        }

        /** Remove a card from the battlefield.
         * @param card The card to remove.
         */
        void removeCard(const Card &card)
        {
            auto card_id = card.getID();
            auto &vec = m_permanents.at(card.getData().getType());
            auto iter = std::find_if(vec.begin(), vec.end(),
                                     [&card_id](const Permanent &other)
                                     { return card_id == other; });
            std::cout << "Removing card " << card.getData().getName()
                      << " with ID " << card_id.getID() << '\n';
            if (iter != vec.end())
            {
                vec.erase(iter);
            }
        }

        void sacrificeCard(Card &card, core::Game &game);

    private:
        PermanentMap m_permanents{
            {CardData::Type::Land, {}},        {CardData::Type::Creature, {}},
            {CardData::Type::Sorcery, {}},     {CardData::Type::Instant, {}},
            {CardData::Type::Enchantment, {}}, {CardData::Type::Artifact, {}},
            {CardData::Type::Planeswalker, {}}};
    };
}; // namespace dandan::core

#endif
