#include "dandan/core/phases/CombatPhase.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/AttackAction.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/core/phases/MainPhase.h"
#include <memory>
#include <string>
#include <vector>

namespace dandan::core
{
    CombatPhase::CombatPhase(Game &game)
        : IPhase(game), m_next_phase(std::make_unique<MainPhase>(game, false))
    {
    }

    [[nodiscard]] std::unique_ptr<IPhase> CombatPhase::handle()
    {
        std::cout << "Handling combat phase\n";
        while (m_step != Step::Done)
        {
            handleNextStep();
        }
        return std::move(m_next_phase);
    }

    void CombatPhase::handleNextStep()
    {
        switch (m_step)
        {
        case Step::BeginningOfCombat:
            // TODO: for now just skip but we should have a priority handler
            // here
            std::cout << "Beginning of combat step\n";
            m_step = Step::DeclareAttackers;
            break;
        // TODO:
        // lists all creatures that could attack and applies actions for every
        // choice should eventually queue the events this generates but for now
        // just handle nullptr events
        case Step::DeclareAttackers:
            std::cout << "Declare attackers step\n";

            // ask the player to choose attacking creatures
            while (true)
            {
                game().render();
                auto viable_attackers{std::vector<Card *>()};
                for (const auto &creature_id :
                     game().activePlayer().battlefield().getCreatures())
                {
                    auto *creature{game().getCardByID(creature_id)};
                    const auto &attack_action{
                        std::make_unique<core::AttackAction>(*creature)};
                    if (!game().isActionPrevented(*attack_action))
                    {
                        viable_attackers.emplace_back(creature);
                    }
                }

                // TODO: technically you should still have priority in this step
                // after declaring no attackers I think
                // check with CR
                if (viable_attackers.empty())
                {
                    break;
                }

                int index{};
                for (const auto *creature : viable_attackers)
                {
                    std::cout << index << " attacker: " << creature << '\n';
                }

                std::cout << "Which creature would you like to attack with: ";
                std::string input{};
                std::getline(game().istream(), input);

                int card_index{std::stoi(input)};

                // TODO: should retry
                if (0 < card_index ||
                    card_index >= static_cast<int>(viable_attackers.size()))
                {
                    break;
                }
                auto attack_action{std::make_unique<core::AttackAction>(
                    *viable_attackers[card_index])};

                auto effect{attack_action->createEffect(game())};
                const auto &final_effect{
                    game().replacementManager().applyReplacementEffects(
                        *effect, game())};

                auto event{final_effect.apply(game())};
                game().eventManager().notify(*event, game());
            }

            m_step = Step::DeclareBlockers;
            break;
        case Step::DeclareBlockers:
            std::cout << "Declare blockers step\n";
            m_step = Step::CombatDamage;
            break;
        case Step::CombatDamage:
            std::cout << "Combat damage step\n";
            m_step = Step::EndOfCombat;
            break;
        case Step::EndOfCombat:
            std::cout << "End of combat step\n";
            m_step = Step::Done;
            break;
        case Step::Done:
            assert(false && "Unreachable code in CombatPhase::handleNextStep");
        }
    }
} // namespace dandan::core
