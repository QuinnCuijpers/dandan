#ifndef DANDAN_CORE_STACK_H
#define DANDAN_CORE_STACK_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <vector>

namespace dandan::core
{
    class Stack
    {
    public:
        Stack() = default;

        void push(std::unique_ptr<effects::IOneShotEffect> &&effect)
        {
            m_stack.push_back(std::move(effect));
        }

        void resolveNext(core::Game &game);

    private:
        std::vector<std::unique_ptr<effects::IOneShotEffect>> m_stack;
    };
} // namespace dandan::core

#endif