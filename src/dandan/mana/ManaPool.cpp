
#include "dandan/mana/Manapool.h"

namespace dandan::mana
{

    void Manapool::add(const ManaBag &mana)
    {
        m_manapool = m_manapool.add(mana);
    }

    [[nodiscard]] const ManaBag &Manapool::view() const
    {
        return m_manapool;
    }

    [[nodiscard]] bool Manapool::canPay(const ManaPrice &price) const
    {
        if (!m_manapool.contains(price.specific()))
        {
            return false;
        }
        return m_manapool.total() >= price.totalRequired();
    }

    bool Manapool::pay(const ManaPrice &price)
    {
        if (!canPay(price))
        {
            return false;
        }

        ManaBag remaining = m_manapool.subtract(price.specific());

        remaining = remaining.subtractAny(price.generic());

        m_manapool = std::move(remaining);
        return true;
    }

    void Manapool::empty()
    {
        m_manapool = ManaBag{};
    }

    /** Outputs the mana to an output stream.
     * @param ostream The output stream.
     * @param mana The mana to output.
     * @return The output stream.
     */
    std::ostream &operator<<(std::ostream &ostream, const Manapool &mana)
    {
        ostream << ManaBag::ManaToSymbols(mana.view());
        return ostream;
    }

}; // namespace dandan::mana
