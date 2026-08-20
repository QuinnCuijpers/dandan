#ifndef DANDAN_MANAPRICE_H
#define DANDAN_MANAPRICE_H

#include "dandan/mana/ManaBag.h"
#include <cstddef>
#include <utility>
namespace dandan::mana

{
    class ManaPrice
    {
    public:
        explicit ManaPrice(ManaBag specific = ManaBag{},
                           size_t generic_amount = {})
            : m_specific{std::move(specific)}, m_generic{generic_amount}
        {
        }

        [[nodiscard]] const ManaBag &specific() const
        {
            return m_specific;
        }

        [[nodiscard]] size_t generic() const
        {
            return m_generic;
        }

        [[nodiscard]] size_t totalRequired() const
        {
            return m_specific.total() + m_generic;
        }

    private:
        ManaBag m_specific;
        size_t m_generic;
    };
} // namespace dandan::mana
#endif
