#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/CardDrawAction.h"
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
            getGame()->render();
            m_step = Step::Upkeep;
            break;
        case Step::Upkeep:
            std::cout << "Handling upkeep step\n";
            getGame()->render();
            m_step = Step::Draw;
            break;
        case Step::Draw:
        {
            // TODO: implement this as a prevention effect instead of hardcoding
            // the first turn rule here
            std::cout << "Handling draw step\n";
            auto draw_action =
                std::make_unique<core::CardDrawAction>(getGame());
            if (getGame()->isActionPrevented(*draw_action))
            {
                std::cout << "Draw prevented\n";
            }
            else
            {
                draw_action->execute();
            }
            getGame()->render();
            m_step = Step::Done;
            break;
        }
        case Step::Done:
            break;
        default:
            std::cerr << "Invalid step in beginning phase\n";
            break;
        }
    }
} // namespace dandan::core