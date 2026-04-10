#ifndef DECK_H
#define DECK_H

#include <deque>
#include <filesystem>
#include <vector>

static auto DANDAN_DECKLIST =
    std::filesystem::path("../../data/temp_decklist.txt");

namespace dandan::core
{
    class Deck
    {

    public:
        Deck();
        explicit Deck(std::filesystem::path path);

        const std::deque<std::string> &getCards() const
        {
            return m_cards;
        }

        std::vector<std::string> draw(int count = 1);

        void peek(int count) const;

    private:
        std::filesystem::path m_decklist_path{DANDAN_DECKLIST};
        std::deque<std::string> m_cards{};

        void loadCards(std::filesystem::path path);
    };
} // namespace dandan::core
#endif