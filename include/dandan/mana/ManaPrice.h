#ifndef DANDAN_MANAPRICE_H
#define DANDAN_MANAPRICE_H

#include "dandan/mana/ManaBag.h"
#include <cstddef>
namespace dandan::mana

{
    class ManaPrice
    {
    public:
        explicit ManaPrice(ManaBag specific = ManaBag{},
                           size_t generic_amount = {});

        [[nodiscard]] const ManaBag &specific() const;

        [[nodiscard]] size_t generic() const;

        [[nodiscard]] size_t totalRequired() const;

    private:
        ManaBag m_specific;
        size_t m_generic;
    };
} // namespace dandan::mana
#endif
