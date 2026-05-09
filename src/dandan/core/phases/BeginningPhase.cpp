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
        return std::make_unique<MainPhase>(game());
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
            game().render();
            m_step = Step::Upkeep;
            break;
        case Step::Upkeep:
            std::cout << "Handling upkeep step\n";
            game().render();
            m_step = Step::Draw;
            break;
        case Step::Draw:
        {
            std::cout << "Handling draw step\n";
            auto draw_action = std::make_unique<core::CardDrawAction>(game());
            if (game().isActionPrevented(*draw_action))
            {
                std::cout << "Draw prevented\n";
            }
            else
            {
                draw_action->createEffect();
            }
            game().render();
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