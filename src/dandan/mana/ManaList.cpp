
#include "dandan/mana/ManaList.h"
#include "dandan/mana/ManaBag.h"

namespace dandan::mana
{
    ManaList::ManaList(ManaBag mana)
    {
        m_options.push_back(std::move(mana));
    }

    /** Constructs a ManaList instance with the specified mana options.
     * @param options The mana options to add.
     */
    ManaList::ManaList(std::vector<ManaBag> options)
        : m_options{std::move(options)}
    {
    }

    /** Returns the list of mana options.
     * @returns The list of mana options.
     */
    [[nodiscard]] const std::vector<ManaBag> &ManaList::getOptions() const
    {
        return m_options;
    }

} // namespace dandan::mana
