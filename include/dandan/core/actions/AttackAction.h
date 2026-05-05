#ifndef DANDAN_ATTACK_ACTION_H
#define DANDAN_ATTACK_ACTION_H

#include "dandan/core/actions/IAction.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::core
{
    class AttackAction : public IAction
    {
    public:
        AttackAction() = default;

        std::unique_ptr<effects::IOneShotEffect> execute() override
        {
            std::cout << "Executing attack action\n";
            return {nullptr};
        }
    };
} // namespace dandan::core

#endif