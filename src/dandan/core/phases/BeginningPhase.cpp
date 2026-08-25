#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/CardTypes.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/CardDrawAction.h"
#include "dandan/core/phases/IPhase.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/UntapEffect.h"
#include "dandan/utils/log.h"

#include <memory>
#include <utility>

// 302.6. A creature’s activated ability with the tap symbol or the untap symbol
// in its activation cost can’t be activated unless the creature has been under
// its controller’s control continuously since their most recent turn began. A
// creature can’t attack unless it has been under its controller’s control
// continuously since their most recent turn began. This rule is informally
// called the “summoning sickness” rule.
namespace dandan::core
{
    BeginningPhase::BeginningPhase(ExecutionContext exec_ctx)
        : IPhase(exec_ctx) {};

    std::unique_ptr<IPhase> BeginningPhase::handle()
    {
        DLOGI << "Handling " << name() << '\n';
        while (m_step != Step::Done)
        {
            handleNextStep();
        }
        DLOGI << "Switching phases to " << m_next_phase->name() << "\n";
        return std::move(m_next_phase);
    }

    [[nodiscard]] std::string BeginningPhase::name() const
    {
        return "Beginning Phase";
    }

    void BeginningPhase::handleUntapStep()
    {
        auto &game{context().state.get()};
        const auto &card_registry{context().cards.get()};

        DLOGI << "Handling untap step\n";

        // untap all permanents for active player, and update summoning sickness
        // for creatures
        for (const auto &[type, cards] :
             game.activePlayer().battlefield().permanents())
        {
            for (const auto &card : cards)
            {
                auto *cardp{card_registry[card]};
                effects::EffectContext effect_context{};
                auto effect{std::make_unique<effects::UntapEffect>(
                    *cardp, effect_context)};
                // TODO: throw generated events onto a queue
                static_cast<void>(effect->apply(context()));

                if (type == Type::Creature)
                {
                    cardp->setSummoningSickness(false);
                }
            }
        }
        game.activePlayer().setPlayedLandThisTurn(false);
        game.render();
        m_step = Step::Upkeep;
    }

    void BeginningPhase::handleNextStep()
    {
        auto &game{context().state.get()};

        switch (m_step)
        {
        case Step::Untap:
            handleUntapStep();
            break;
        case Step::Upkeep:
            DLOGI << "Handling upkeep step\n";
            game.priorityManager().setPriorityToPlayer(
                game.activePlayer().getID(), context());
            game.render();
            m_step = Step::Draw;
            break;
        case Step::Draw:
        {
            DLOGI << "Handling draw step\n";
            auto draw_action = std::make_unique<core::CardDrawAction>(
                game.activePlayer().getID());
            if (game.isActionPrevented(*draw_action))
            {
                DLOGI << "Draw prevented\n";
            }
            else
            {
                // TODO: cast draweffect to game instead of handling in the
                // createEffect of the action
                auto draw_effect{draw_action->createEffect(context())};
                const auto &final_effect{
                    game.replacementManager().applyReplacementEffects(
                        *draw_effect, context())};
                static_cast<void>(final_effect->apply(context()));
            }
            game.priorityManager().setPriorityToPlayer(
                game.activePlayer().getID(), context());
            game.render();
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
