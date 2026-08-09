#ifndef DANDAN_ATTACK_ACTION_H
#define DANDAN_ATTACK_ACTION_H

#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
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
        explicit AttackAction(core::Card &creature);

        [[nodiscard]] ActionActor getActor() const override;

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            [[maybe_unused]] core::Game &game) override;

    private:
        Card &m_creature;
    };
} // namespace dandan::core

#endif
