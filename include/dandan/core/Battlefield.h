#ifndef DANDAN_BOARD_H
#define DANDAN_BOARD_H

#include "Card.h"
#include "dandan/core/CardData.h"
#include <unordered_map>
#include <vector>

namespace dandan::core
{

    using Permanent = Card;
    using PermanentMap =
        std::unordered_map<CardData::Type, std::vector<Permanent>>;

    class Battlefield
    {
    public:
        void addCard(Card card)
        {
            card.setZone(Zone::BATTLEFIELD);
            m_permanents[card.getData().getType()].emplace_back(card);
        }

        [[nodiscard]] PermanentMap &permanents()
        {
            return m_permanents;
        }

        [[nodiscard]] const PermanentMap &getPermanents() const
        {
            return m_permanents;
        }

        // [[nodiscard]] Permanent getPermanent(int card_index)
        // {
        //     auto card{m_permanents[card_index]};
        //     // erase chosen over pop and swap as we want to maintain card
        //     order
        //     // in hand while in the backend it is more effiecient to pop and
        //     // swap, the order of cards remaining constant makes UI later
        //     easier
        //     // to implement
        //     m_permanents.erase(m_permanents.begin() + card_index);
        //     return card;
        // }

        [[nodiscard]] const std::vector<Permanent> &getLands() const
        {
            return m_permanents.at(CardData::Type::Land);
        }

        [[nodiscard]] Permanent getLand(int card_index)
        {
            auto &vec = m_permanents.at(CardData::Type::Land);
            auto card = vec[card_index];
            vec.erase(vec.begin() + card_index);
            return card;
        }

        [[nodiscard]] const std::vector<Permanent> &getCreatures() const
        {
            return m_permanents.at(CardData::Type::Creature);
        }

    private:
        PermanentMap m_permanents{
            {CardData::Type::Land, {}},        {CardData::Type::Creature, {}},
            {CardData::Type::Sorcery, {}},     {CardData::Type::Instant, {}},
            {CardData::Type::Enchantment, {}}, {CardData::Type::Artifact, {}},
            {CardData::Type::Planeswalker, {}}};
    };
}; // namespace dandan::core

#endif