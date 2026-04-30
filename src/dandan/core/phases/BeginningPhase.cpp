#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/Game.h"
#include "dandan/core/phases/IPhase.h"
#include "dandan/core/phases/MainPhase.h"
#include <memory>

namespace dandan::core
{

    std::unique_ptr<IPhase> BeginningPhase::handle()
    {
        std::cout << "Handling beginning phase\n";
        while (m_step != Step::Done)
        {
            handleNextStep();
        }
        return std::make_unique<MainPhase>(getGame());
    }

    void BeginningPhase::handleNextStep()
    {
        switch (m_step)
        {
        case Step::Untap:
            std::cout << "Handling untap step\n";
            // Go through all permanents and untap them
            // as this could trigger effects, we need to go through the event
            // manager so we apply an untap effect to all permanents and trigger
            // any effects that trigger on untapping although all untaps resolve
            // simultaneous and immediately
            m_step = Step::Upkeep;
            break;
        case Step::Upkeep:
            std::cout << "Handling upkeep step\n";
            m_step = Step::Draw;
            break;
        case Step::Draw:
            // TODO: implement this as a prevention effect instead of hardcoding
            // the first turn rule here
            std::cout << "Handling draw step\n";
            if (!getGame()->isFirstTurn())
            {
                std::cout << "Active player draws a card\n";
                getGame()->getActivePlayer().drawCard(getGame()->getDeck());
            }
            else
            {
                std::cout << "Skipping draw step for starting player\n";
            }
            m_step = Step::Done;
            break;
        default:
            std::cerr << "Invalid step in beginning phase\n";
            break;
        }
    }
} // namespace dandan::core