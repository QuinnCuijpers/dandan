#include "dandan/costs/ManaCost.h"
#include "dandan/mana/Mana.h"

namespace dandan::costs
{

    std::string ManaCost::display([[maybe_unused]] bool isFinal) const
    {
        std::string res{};
        res += mana::ManaToSymbols(m_mana->getMana());
        return res;
    }

} // namespace dandan::costs