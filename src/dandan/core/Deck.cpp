#include "dandan/core/Deck.h"
#include "dandan/core/Card.h"
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#ifdef DANDAN_BUILD_SERIALIZE
#include <algorithm>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#endif

namespace dandan::core
{

#ifdef DANDAN_BUILD_SERIALIZE
    Deck::Deck()
    {
        std::cout << "No decklist path provided. Using default: "
                  << m_decklist_path.filename() << '\n';
        loadCards(m_decklist_path);
        std::cout << "Deck initialized with default decklist.\n";
    }

    Deck::Deck(std::filesystem::path path) : m_decklist_path(std::move(path))
    {
        loadCards(m_decklist_path);
    }

    void Deck::loadCards(std::filesystem::path path)
    {
        std::ifstream file{path};
        while (file)
        {
            std::string line;
            std::getline(file, line);
            if (!line.empty())
            {
                std::stringstream ss{line};
                std::string name;
                int amount;
                ss >> amount;
                ss.ignore(1, ' '); // Ignore the space after the amount
                std::getline(ss, name);
                std::cout << "Adding " << amount << " copies of " << name
                          << " to the deck.\n";
                for (int i = 0; i < amount; ++i)
                {
                    m_cards.emplace_back(std::make_unique<Card>(name));
                }
            }
        }
        std::shuffle(m_cards.begin(), m_cards.end(), std::random_device{});
    }
#endif

    std::vector<std::unique_ptr<Card>> Deck::draw(int count)
    {
        std::vector<std::unique_ptr<Card>> drawn_cards;
        for (int i = 0; i < count && !m_cards.empty(); ++i)
        {
            drawn_cards.push_back(std::move(m_cards.front()));
            m_cards.pop_front();
        }
        return drawn_cards;
    }

    void Deck::peek(int count) const
    {
        for (int i = 0; i < count && i < static_cast<int>(m_cards.size()); ++i)
        {
            const std::unique_ptr<Card> &card = m_cards[i];
            std::cout << "card " << i << " from the top: " << *(card.get())
                      << '\n';
        }
    }
} // namespace dandan::core