#include "dandan/core/CardRegistry.h"
#include "dandan/core/Card.h"
#include "dandan/utils/log.h"
#include <fstream>

namespace dandan::core
{
#ifdef DANDAN_SERIALIZE
    void CardRegistry::load_cards(const std::filesystem::path &path)
    {
        std::ifstream file{path};
        while (file)
        {
            std::string line;
            std::getline(file, line);
            if (!line.empty())
            {
                std::stringstream stream{line};
                std::string name;
                int amount{};
                stream >> amount;
                stream.ignore(1, ' '); // Ignore the space after the amount
                std::getline(stream, name);
                DLOGI << "Adding " << amount << " copies of " << name
                      << " to the library.\n";
                for (int i = 0; i < amount; ++i)
                {
                    m_cards.emplace_back(name);
                }
            }
        }
    }
#endif

    CardRegistry::CardRegistry(std::optional<std::filesystem::path> path)
    {
#ifdef DANDAN_SERIALIZE
        if (path.has_value())
        {
            load_cards(path.value());
        }
#endif

        for (auto &card : m_cards)
        {
            auto bound_abilities{std::vector<abilities::BoundAbility>{}};
            for (const auto &ability : card.getData().abilities)
            {
                auto *definition{ability.get()};
                auto bound{abilities::BoundAbility{*definition, &card}};
                bound_abilities.push_back(bound);
            }
            card.setBoundAbilities(std::move(bound_abilities));
        }

        for (auto &card : m_cards)
        {
            m_card_lookup.emplace(card.getID(), &card);
        }
    }

    std::vector<CardID> CardRegistry::card_ids() const
    {
        std::vector<CardID> card_ids;
        card_ids.reserve(m_cards.size());
        std::transform(m_cards.begin(), m_cards.end(),
                       std::back_inserter(card_ids),
                       [](const auto &card) { return card.getID(); });
        return card_ids;
    }

    std::vector<Card *> CardRegistry::cards() const
    {
        std::cout << "m_cards: " << m_cards.size() << '\n';
        std::cout << "m_card_lookup: " << m_card_lookup.size() << '\n';
        std::vector<Card *> cards;
        cards.reserve(m_cards.size());
        std::transform(m_card_lookup.begin(), m_card_lookup.end(),
                       std::back_inserter(cards),
                       [](const auto &iter) { return iter.second; });
        std::cout << "Cards size when calling cards(): " << cards.size()
                  << '\n';
        return cards;
    }

    void CardRegistry::setCards(std::deque<Card> cards)
    {
        m_cards = std::move(cards);

        m_card_lookup.clear();

        for (auto &card : m_cards)
        {
            m_card_lookup[card.getID()] = &card;
        }
    }

    Card *CardRegistry::operator[](CardID card_id) const
    {
        return m_card_lookup.at(card_id);
    }

    Card *CardRegistry::operator[](int card_id) const
    {
        return m_card_lookup.at(CardID::fromInt(card_id));
    }

} // namespace dandan::core
