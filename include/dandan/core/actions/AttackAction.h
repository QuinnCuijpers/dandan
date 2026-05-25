#ifndef DANDAN_ATTACK_ACTION_H
#define DANDAN_ATTACK_ACTION_H

#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
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
        AttackAction() = default;

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            [[maybe_unused]] core::Game &game) override
        {
            std::cout << "Executing attack action\n";
            return {nullptr};
        }
    };
} // namespace dandan::core

#endif
