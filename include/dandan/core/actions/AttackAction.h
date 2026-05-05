#ifndef DANDAN_ATTACK_ACTION_H
#define DANDAN_ATTACK_ACTION_H

#include "dandan/core/actions/IAction.h"
#include <iostream>

namespace dandan::core
{
    class AttackAction : public IAction
    {
    public:
        AttackAction() = default;

        void execute() override
        {
            std::cout << "Executing attack action\n";
        }
    };
} // namespace dandan::core

#endif