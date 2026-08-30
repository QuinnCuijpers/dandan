#include "dandan/core/phases/CombatPhase.h"
#include "dandan/core/actions/AttackAction.h"
#include "dandan/core/phases/MainPhase.h"
#include <memory>
#include <string>
#include <vector>

namespace dandan::core
{
    CombatPhase::CombatPhase(ExecutionContext exec_ctx)
        : IPhase(exec_ctx),
          m_next_phase(std::make_unique<MainPhase>(exec_ctx, false))
    {
    }

    [[nodiscard]] std::unique_ptr<IPhase> CombatPhase::handle()
    {
        std::cout << "Handling " << name() << '\n';
        while (m_step != Step::Done)
        {
            handleNextStep();
        }
        return std::move(m_next_phase);
    }

    [[nodiscard]] std::string CombatPhase::name() const
    {
        return "Combat Phase";
    }

    void CombatPhase::addAttacker(Card *creature)
    {
        m_attackers.emplace_back(creature);
    }

    /** Adds a blocker to the specified attacking creature.
     * @param attacking_creature The attacking creature to add the blocker
     * to.
     * @param blocking_creature The creature to add as a blocker.
     */
    void CombatPhase::addBlocker(Card *attacking_creature,
                                 Card *blocking_creature)
    {
        attacking_creature->setBlocked(true);
        blocking_creature->setBlocking(true);
        m_blockers[attacking_creature].emplace_back(blocking_creature);
    }

    void CombatPhase::handleDeclareAttackersStep()
    {
        auto &game{context().state.get()};
        auto &card_registry{context().cards.get()};
        auto &priority_manager{context().priority_manager.get()};
        auto &event_manager{context().event_manager.get()};
        auto &istream{context().input.get()};
        auto &replacement_manager{context().replacement_manager.get()};
        auto &prevention_manager{context().prevention_manager.get()};

        priority_manager.setPriorityToPlayer(game.activePlayer().getID(),
                                             context());
        std::cout << "Declare attackers step\n";

        // ask the player to choose attacking creatures
        while (true)
        {
            game.render(card_registry);
            auto viable_attackers{std::vector<Card *>()};
            for (const auto &creature_id :
                 game.activePlayer().battlefield().getCreatures())
            {
                auto *creature{card_registry[creature_id]};
                const auto &attack_action{
                    std::make_unique<core::AttackAction>(*creature)};
                if (!prevention_manager.isPrevented(*attack_action, context()))
                {
                    std::cout << "Creature " << creature->getData().name
                              << " (CardID: " << creature->getID().getID()
                              << ") can attack\n";
                    std::cout << "Summoning sickness: " << std::boolalpha
                              << creature->getSummoningSickness() << '\n';
                    std::cout << "Is attacking: " << creature->isAttacking()
                              << '\n';
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
                std::cout << index << " attacker: " << *creature << '\n';
            }

            std::cout << "Which creature would you like to attack with (or "
                         "none to move to the next step): ";
            std::string input{};
            std::getline(istream, input);

            if (input == "none")
            {
                break;
            }

            int card_index{std::stoi(input)};

            // TODO: should retry
            if (0 < card_index ||
                card_index >= static_cast<int>(viable_attackers.size()))
            {
                break;
            }
            auto attack_action{std::make_unique<core::AttackAction>(
                *viable_attackers[card_index])};

            auto effect{attack_action->createEffect(context())};
            const auto &final_effect{
                replacement_manager.applyReplacementEffects(*effect,
                                                            context())};

            auto event{final_effect->apply(context())};
            if (event != nullptr)
            {
                event_manager.notify(*event, context());
            }
        }

        m_step = Step::DeclareBlockers;
    }
    void CombatPhase::handleDeclareBlockersStep()
    {
        auto &game{context().state.get()};
        auto &card_registry{context().cards.get()};
        auto &priority_manager{context().priority_manager.get()};
        auto &istream{context().input.get()};

        std::cout << "Declare blockers step\n";
        priority_manager.setPriorityToPlayer(game.activePlayer().getID(),
                                             context());
        if (m_attackers.empty())
        {
            std::cout
                << "No attackers declared, skipping declare blockers step\n";
            m_step = Step::CombatDamage;
            return;
        }
        auto *blocking_player{&game.nonActivePlayer()};
        game.render(card_registry);
        for (const auto &creature_id :
             blocking_player->battlefield().getCreatures())
        {
            auto *creature{card_registry[creature_id]};
            if (creature->getTapped() || creature->isBlocking())
            {
                continue;
            }
            std::cout << "Which attacker would you like to block with "
                      << creature->getData().name
                      << " (or none to not block with it): ";
            std::string input{};
            std::getline(istream, input);
            if (input == "none")
            {
                continue;
            }
            // for now let this be a card ID instead of index
            int card_id{std::stoi(input)};
            auto *attacking_creature{card_registry[card_id]};
            if (attacking_creature == nullptr ||
                !attacking_creature->isAttacking())
            {
                std::cout << "Invalid attacker chosen\n";
                continue;
            }
            addBlocker(attacking_creature, creature);
            std::cout << creature->getData().name << " is blocking "
                      << attacking_creature->getData().name << '\n';
        }
        m_step = Step::CombatDamage;
    }

    void CombatPhase::handleNextStep()
    {
        auto &game{context().state.get()};
        auto &priority_manager{context().priority_manager.get()};

        switch (m_step)
        {
        case Step::BeginningOfCombat:
            std::cout << "Beginning of combat step\n";
            priority_manager.setPriorityToPlayer(game.activePlayer().getID(),
                                                 context());
            m_step = Step::DeclareAttackers;
            break;
        // TODO:
        // lists all creatures that could attack and applies actions for every
        // choice should eventually queue the events this generates but for now
        // just handle nullptr events
        case Step::DeclareAttackers:
            handleDeclareAttackersStep();
            break;
        case Step::DeclareBlockers:
            handleDeclareBlockersStep();
            break;
        case Step::CombatDamage:
            std::cout << "Combat damage step\n";
            for (auto *creature : m_attackers)
            {
                if (!creature->isBlocked())
                {
                    std::cout << "Dealing damage to opponent from "
                              << creature->getData().name << '\n';
                    game.nonActivePlayer().takeDamage(creature->getPower(),
                                                      context());
                }
                else
                {
                    std::cout << "Dealing damage to blocking creature from "
                              << creature->getData().name << '\n';
                    for (auto *blocking_creature : m_blockers[creature])
                    {
                        std::cout << "Dealing damage to attacking creature "
                                  << creature->getID().getID()
                                  << " from blocking creature "
                                  << blocking_creature->getID().getID() << '\n';
                        creature->takeDamage(blocking_creature->getPower(),
                                             context());
                        blocking_creature->takeDamage(creature->getPower(),
                                                      context());
                    }
                }
            }
            m_step = Step::EndOfCombat;
            break;
        case Step::EndOfCombat:
            priority_manager.setPriorityToPlayer(game.activePlayer().getID(),
                                                 context());
            std::cout << "End of combat step\n";
            m_step = Step::Done;
            break;
        case Step::Done:
            assert(false && "Unreachable code in CombatPhase::handleNextStep");
        }
    }
} // namespace dandan::core
