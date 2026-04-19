#include "dandan/abilities/ManaAbility.h"
#include "dandan/mana/Mana.h"
#include "dandan/mana/ManaList.h"
#include <iostream>

namespace dandan::abilities
{

    void ManaAbility::resolve() const
    {
        for (const auto &option : m_mana_list.getOptions())
        {
            std::cout << "Resolving ManaAbility: "
                      << mana::ManaToSymbols(option->getMana()) << " mana\n";
        }
    }

} // namespace dandan::abilities