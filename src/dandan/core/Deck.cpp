#include "dandan/core/Deck.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace dandan::core
{

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
                    m_cards.emplace_back(name);
                }
            }
        }
        std::shuffle(m_cards.begin(), m_cards.end(), std::random_device{});
    }

    std::vector<std::string> Deck::draw(int count)
    {
        std::vector<std::string> drawn_cards;
        for (int i = 0; i < count && !m_cards.empty(); ++i)
        {
            drawn_cards.push_back(m_cards.front());
            m_cards.pop_front();
        }
        return drawn_cards;
    }

    void Deck::peek(int count) const
    {
        for (int i = 0; i < count && i < static_cast<int>(m_cards.size()); ++i)
        {
            const std::string &card = m_cards[i];
            std::cout << "card " << i << " from the top: " << card << '\n';
        }
    }
} // namespace dandan::core