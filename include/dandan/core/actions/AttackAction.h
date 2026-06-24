#ifndef DANDAN_ATTACK_ACTION_H
#define DANDAN_ATTACK_ACTION_H

#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/AttackEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::core
{
    /**
     * @brief An action that represents an attack.
     * @class AttackAction
     *
     * @implements IAction
     */
    class AttackAction : public IAction
    {
    public:
        /** Constructor
         * @param creature the creature card that would attack
         */
        explicit AttackAction(core::Card &creature) : m_creature{creature}
        {
        }

        [[nodiscard]] ActionActor getActor() const override
        {
            return m_creature.getID();
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            [[maybe_unused]] core::Game &game) override
        {
            std::cout << "Executing attack action\n";
            effects::EffectContext context{m_creature.getID()};
            return std::make_unique<effects::AttackEffect>(m_creature, context);
        }

    private:
        Card &m_creature;
    };
} // namespace dandan::core

#endif
