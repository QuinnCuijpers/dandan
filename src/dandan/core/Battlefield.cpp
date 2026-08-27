#include "dandan/core/Battlefield.h"
#include "dandan/core/Game.h"

namespace dandan::core
{

    void Battlefield::addCard(Card &card)
    {
        card.setZone(Zone::BATTLEFIELD);
        m_permanents[card.getData().type].emplace_back(card.getID());
    }

    [[nodiscard]] PermanentMap &Battlefield::permanents()
    {
        return m_permanents;
    }

    [[nodiscard]] const PermanentMap &Battlefield::permanents() const
    {
        return m_permanents;
    }

    [[nodiscard]] const std::vector<Permanent> &Battlefield::getLands() const
    {
        return m_permanents.at(Type::Land);
    }

    /** Get the creatures on the battlefield.
     * @return A const reference to the creatures vector.
     */
    [[nodiscard]] const std::vector<Permanent> &Battlefield::getCreatures()
        const
    {
        return m_permanents.at(Type::Creature);
    }

    /** Get a land from the battlefield, the land is removed from the
     * battlefield.
     * @param card_index The index of the land to get.
     * @return The land at the specified index.
     */
    [[nodiscard]] Permanent Battlefield::getLand(int card_index)
    {
        auto &vec = m_permanents.at(Type::Land);
        auto card = vec[card_index];
        vec.erase(vec.begin() + card_index);
        return card;
    }

    /** Remove a card from the battlefield.
     * @param card The card to remove.
     */
    void Battlefield::removeCard(const Card &card)
    {
        auto card_id = card.getID();
        auto &vec = m_permanents.at(card.getData().type);
        auto iter = std::find_if(vec.begin(), vec.end(),
                                 [&card_id](const Permanent &other)
                                 { return card_id == other; });
        std::cout << "Removing card " << card.getData().name << " with ID "
                  << card_id.getID() << '\n';
        if (iter != vec.end())
        {
            vec.erase(iter);
        }
    }
    void Battlefield::sacrificeCard(Card &card, core::ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};

        removeCard(card);
        game.graveyard().addCard(card);
    }
} // namespace dandan::core
