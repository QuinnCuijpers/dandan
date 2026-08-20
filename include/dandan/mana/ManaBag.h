#ifndef DANDAN_MANABAG_H
#define DANDAN_MANABAG_H

#include "dandan/mana/ManaType.h"
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <map>
#include <string>

namespace dandan::mana
{
    class ManaBag
    {
    public:
        explicit ManaBag(
            std::initializer_list<std::pair<ManaType, size_t>> init_list);

        [[nodiscard]] std::size_t get(ManaType type) const;

        [[nodiscard]] bool contains(const ManaBag &other) const;

        [[nodiscard]] size_t total() const;

        [[nodiscard]] ManaBag subtract(const ManaBag &other) const;

        [[nodiscard]] ManaBag subtractAny(size_t amount) const;

        [[nodiscard]] ManaBag add(const ManaBag &other) const;

        [[nodiscard]] bool empty() const;

        [[nodiscard]] const std::map<ManaType, std::size_t> &data() const;

        [[maybe_unused]]
        static std::string ManaToSymbols(const dandan::mana::ManaBag &mana);

        friend std::ostream &operator<<(std::ostream &ostream,
                                        const ManaBag &mana);

    private:
        std::map<ManaType, std::size_t> m_map;
    };
} // namespace dandan::mana

#endif
