#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/CardDrawAction.h"
#include "dandan/core/phases/IPhase.h"
#include "dandan/log.h"
#include <memory>

namespace dandan::core
{

    std::unique_ptr<IPhase> BeginningPhase::handle()
    {
        DLOGI << "Handling beginning phase\n";
        while (m_step != Step::Done)
        {
            handleNextStep();
        }
        // TODO: add proper streaming to phases such that we can remove the
        // typeid name
        DLOGI << "Switching phases to " << typeid(*m_next_phase).name() << "\n";
        return std::move(m_next_phase);
    }

    void BeginningPhase::handleNextStep()
    {
        switch (m_step)
        {
        case Step::Untap:
            DLOGI << "Handling untap step\n";
            // Go through all permanents and untap them
            // as this could trigger effects, we need to go through the event
            // manager so we apply an untap effect to all permanents and trigger
            // any effects that trigger on untapping although all untaps resolve
            // simultaneous and immediately
            game().activePlayer().setPlayedLandThisTurn(false);
            game().render();
            m_step = Step::Upkeep;
            break;
        case Step::Upkeep:
            DLOGI << "Handling upkeep step\n";
            game().render();
            m_step = Step::Draw;
            break;
        case Step::Draw:
        {
            DLOGI << "Handling draw step\n";
            auto draw_action = std::make_unique<core::CardDrawAction>(game());
            if (game().isActionPrevented(*draw_action))
            {
                DLOGI << "Draw prevented\n";
            }
            else
            {
                // TODO: cast draweffect to game instead of handling in the
                // createEffect of the action
                draw_action->createEffect();
            }
            game().render();
            m_step = Step::Done;
            break;
        }
        case Step::Done:
            assert(false &&
                   "Unreachable code in BeginningPhase::handleNextStep");
            break;
        }
    }
} // namespace dandan::core