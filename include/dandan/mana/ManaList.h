#ifndef DANDAN_MANALIST_H
#define DANDAN_MANALIST_H

#include "Mana.h"
#include <memory>
#include <vector>

namespace dandan::mana
{
    class ManaList
    {
    public:
        explicit ManaList(std::unique_ptr<Mana> mana)
        {
            m_options.push_back(std::move(mana));
        }

        explicit ManaList(std::vector<std::unique_ptr<Mana>> options)
            : m_options{std::move(options)}
        {
        }

        const std::vector<std::unique_ptr<Mana>> &getOptions() const
        {
            return m_options;
        }

    private:
        std::vector<std::unique_ptr<Mana>> m_options{};
    };
} // namespace dandan::mana

#endif // DANDAN_MANALIST_H