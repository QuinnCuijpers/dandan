#include "dandan/mana/ManaPrice.h"

namespace dandan::mana

{
    ManaPrice::ManaPrice(ManaBag specific, size_t generic_amount)
        : m_specific{std::move(specific)}, m_generic{generic_amount}
    {
    }

    [[nodiscard]] const ManaBag &ManaPrice::specific() const
    {
        return m_specific;
    }

    [[nodiscard]] size_t ManaPrice::generic() const
    {
        return m_generic;
    }

    [[nodiscard]] size_t ManaPrice::totalRequired() const
    {
        return m_specific.total() + m_generic;
    }

}; // namespace dandan::mana
