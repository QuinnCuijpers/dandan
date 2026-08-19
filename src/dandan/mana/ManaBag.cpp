#include "dandan/mana/ManaBag.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace dandan::mana

{
    ManaBag::ManaBag(
        std::initializer_list<std::pair<ManaType, size_t>> init_list)
    {
        for (const auto &[color, amt] : init_list)
        {
            m_map[color] += amt; // merge duplicates
        }
    }

    [[nodiscard]] std::size_t ManaBag::get(ManaType type) const
    {
        auto iter{m_map.find(type)};
        return iter != m_map.end() ? iter->second : 0;
    }

    [[nodiscard]] bool ManaBag::contains(const ManaBag &other) const
    {
        return std::all_of(
            other.data().begin(), other.data().end(),
            [this](const auto &pair)
            {
                std::cout << "Color num: " << (int)pair.first << '\n';
                std::cout << "gotten: " << get(pair.first) << '\n';
                std::cout << "amount req: " << pair.second << '\n';
                return get(pair.first) >= pair.second;
            });
    }

    [[nodiscard]] size_t ManaBag::total() const
    {
        size_t result{};
        for (const auto &[color, amount] : m_map)
        {
            result += amount;
        }
        return result;
    }

    [[nodiscard]] ManaBag ManaBag::subtract(const ManaBag &other) const
    {
        assert(contains(other));

        ManaBag result = *this;
        for (const auto &[color, amt] : other.m_map)
        {
            result.m_map[color] -= amt;
            if (result.m_map[color] == 0)
            {
                result.m_map.erase(color);
            }
        }
        return result;
    }

    [[nodiscard]] ManaBag ManaBag::subtractAny(size_t amount) const
    {
        ManaBag result = *this;
        if (amount > result.total())
        {
            throw std::invalid_argument("Not enough total mana");
        }

        // Remove from Colorless
        size_t colorlessAmt = result.get(ManaType::COLORLESS);
        size_t removeFromColorless = std::min(colorlessAmt, amount);
        result.m_map[ManaType::COLORLESS] -= removeFromColorless;
        amount -= removeFromColorless;
        if (result.m_map[ManaType::COLORLESS] == 0)
        {
            result.m_map.erase(ManaType::COLORLESS);
        }

        // Remove from colored in WUBRG order
        for (auto &[type, amt] : result.m_map)
        {
            if (amount == 0)
            {
                break;
            }
            if (type == ManaType::COLORLESS)
            {
                continue;
            }
            size_t remove = std::min(amt, amount);
            result.m_map[type] -= remove;
            amount -= remove;
            if (result.m_map[type] == 0)
            {
                result.m_map.erase(type);
            }
        }
        return result;
    }

    [[nodiscard]] ManaBag ManaBag::add(const ManaBag &other) const
    {
        ManaBag result = *this;
        for (const auto &[color, amt] : other.m_map)
        {
            result.m_map[color] += amt;
        }
        return result;
    }

    [[nodiscard]] bool ManaBag::empty() const
    {
        return m_map.empty();
    }

    [[nodiscard]] const std::map<ManaType, std::size_t> &ManaBag::data() const
    {
        return m_map;
    }

    std::string ManaBag::ManaToSymbols(const dandan::mana::ManaBag &mana)
    {
        if (mana.empty())
        {
            return std::string{};
        }

        std::string symbols{};
        for (const auto &[mana_type, amount] : mana.data())
        {
            std::string symbol{};
            switch (mana_type)
            {
            case ManaType::COLORLESS:
                symbol = "C";
                break;
            case ManaType::WHITE:
                symbol = "W";
                break;
            case ManaType::BLUE:
                symbol = "U";
                break;
            case ManaType::BLACK:
                symbol = "B";
                break;
            case ManaType::RED:
                symbol = "R";
                break;
            case ManaType::GREEN:
                symbol = "G";
                break;
            }

            for (size_t i = 0; i < amount; ++i)
            {
                symbols += symbol;
            }
        }

        return symbols;
    }

    std::ostream &operator<<(std::ostream &ostream, const ManaBag &mana)
    {
        ostream << ManaBag::ManaToSymbols(mana);
        return ostream;
    }

} // namespace dandan::mana
