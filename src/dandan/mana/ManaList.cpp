
#include "dandan/mana/ManaList.h"

namespace dandan::mana
{
    ManaList::ManaList(std::unique_ptr<Manapool> mana)
    {
        m_options.push_back(std::move(mana));
    }

    /** Constructs a ManaList instance with the specified mana options.
     * @param options The mana options to add.
     */
    ManaList::ManaList(std::vector<std::unique_ptr<Manapool>> options)
        : m_options{std::move(options)}
    {
    }

    /** Returns the list of mana options.
     * @returns The list of mana options.
     */
    [[nodiscard]] const std::vector<std::unique_ptr<Manapool>> &ManaList::
        getOptions() const
    {
        return m_options;
    }

} // namespace dandan::mana
