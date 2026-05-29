#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/CardData.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/CardDrawAction.h"
#include "dandan/core/phases/IPhase.h"
#include "dandan/effects/one_shot/UntapEffect.h"
#include "dandan/log.h"
#include <memory>

// 302.6. A creature’s activated ability with the tap symbol or the untap symbol
// in its activation cost can’t be activated unless the creature has been under
// its controller’s control continuously since their most recent turn began. A
// creature can’t attack unless it has been under its controller’s control
// continuously since their most recent turn began. This rule is informally
// called the “summoning sickness” rule.
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
        DLOGI << "Switching phases to " << m_next_phase->name() << "\n";
        return std::move(m_next_phase);
    }

    void BeginningPhase::handleUntapStep()
    {
        DLOGI << "Handling untap step\n";

        // untap all permanents for active player, and update summoning sickness
        // for creatures
        for (auto &[type, cards] :
             game().activePlayer().battlefield().permanents())
        {
            for (auto &card : cards)
            {
                auto *cardp{game().getCardByID(card)};
                auto effect{std::make_unique<effects::UntapEffect>(*cardp)};
                // TODO: throw generated events onto a queue
                effect->apply(game());

                if (type == CardData::Type::Creature)
                {
                    cardp->setSummoningSickness(false);
                }
            }
        }

        game().activePlayer().setPlayedLandThisTurn(false);
        game().render();
        m_step = Step::Upkeep;
    }

    void BeginningPhase::handleNextStep()
    {
        switch (m_step)
        {
        case Step::Untap:
            handleUntapStep();
            break;
        case Step::Upkeep:
            DLOGI << "Handling upkeep step\n";
            game().render();
            m_step = Step::Draw;
            break;
        case Step::Draw:
        {
            DLOGI << "Handling draw step\n";
            auto draw_action = std::make_unique<core::CardDrawAction>(
                game().activePlayer().getID());
            if (game().isActionPrevented(*draw_action))
            {
                DLOGI << "Draw prevented\n";
            }
            else
            {
                // TODO: cast draweffect to game instead of handling in the
                // createEffect of the action
                draw_action->createEffect(game());
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