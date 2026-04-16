#ifndef DANDAN_CORE_STACK_H
#define DANDAN_CORE_STACK_H

#include "dandan/abilities/IAbility.h"
#include <memory>
#include <vector>

namespace dandan::core
{
    class Stack
    {
    public:
        Stack() = default;

        void push(const std::unique_ptr<abilities::IAbility> &ability)
        {
            m_stack.push_back(ability.get());
        }

        void resolveNext();

    private:
        std::vector<abilities::IAbility *> m_stack{};
    };
} // namespace dandan::core

#endif