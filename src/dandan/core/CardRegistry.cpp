#include "dandan/core/CardRegistry.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/utils/log.h"
#include <fstream>
#include <vector>

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
                    auto card{Card{name}};
                    auto bound_abilities{
                        std::vector<abilities::BoundAbility>{}};
                    for (const auto &ability : card.getData().abilities)
                    {
                        auto *definition{ability.get()};
                        auto bound{abilities::BoundAbility{*definition, &card}};
                        bound_abilities.push_back(bound);
                    }
                    card.setBoundAbilities(std::move(bound_abilities));
                    m_card_lookup.insert_or_assign(card.getID(), card);
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
    }

    std::vector<CardID> CardRegistry::card_ids() const
    {
        std::vector<CardID> cards;
        cards.reserve(m_card_lookup.size());
        std::transform(m_card_lookup.begin(), m_card_lookup.end(),
                       std::back_inserter(cards),
                       [](const auto &iter) { return iter.first; });
        std::cout << "Cards size when calling cards(): " << cards.size()
                  << '\n';
        return cards;
    }

    void CardRegistry::setCards(const std::vector<Card> &cards)
    {

        m_card_lookup.clear();

        for (const auto &card : cards)
        {
            m_card_lookup.insert_or_assign(card.getID(), card);
        }
    }

    Card &CardRegistry::operator[](CardID card_id)
    {
        return m_card_lookup.at(card_id);
    }

    Card &CardRegistry::operator[](int card_id)
    {
        return m_card_lookup.at(CardID::fromInt(card_id));
    }

    const Card &CardRegistry::operator[](CardID card_id) const
    {
        return m_card_lookup.at(card_id);
    }

    const Card &CardRegistry::operator[](int card_id) const
    {
        return m_card_lookup.at(CardID::fromInt(card_id));
    }

} // namespace dandan::core
