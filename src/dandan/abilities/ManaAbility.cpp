#include "dandan/abilities/ManaAbility.h"
#include "dandan/core/Game.h"
#include "dandan/mana/Mana.h"
#include "dandan/mana/ManaList.h"
#include <iostream>

namespace dandan::abilities
{

    void ManaAbility::resolve([[maybe_unused]] core::Game &game) const
    {
        for (const auto &option : m_mana_list.getOptions())
        {
            std::cout << "Resolving ManaAbility: "
                      << mana::ManaToSymbols(option->getMana()) << " mana\n";
        }
    }

} // namespace dandan::abilities