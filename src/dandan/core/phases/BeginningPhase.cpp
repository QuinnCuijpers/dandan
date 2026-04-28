#include "dandan/core/phases/BeginningPhase.h"

namespace dandan::core
{
    void BeginningPhase::handle()
    {
        switch (m_step)
        {
        case Step::Untap:
            std::cout << "Handling untap step\n";
            m_step = Step::Upkeep;
            break;
        case Step::Upkeep:
            std::cout << "Handling upkeep step\n";
            m_step = Step::Draw;
            break;
        case Step::Draw:
            std::cout << "Handling draw step\n";
            m_step = Step::Untap;
            break;
        }
    }
} // namespace dandan::core