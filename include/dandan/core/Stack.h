#ifndef DANDAN_CORE_STACK_H
#define DANDAN_CORE_STACK_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <vector>

namespace dandan::core
{
    /** @brief The class that represents the stack that holds effects that are about to
     * `apply`
     * @class Stack
     */
    class Stack
    {
    public:
        Stack() = default;

        /** Pushes an effect onto the stack.
         * @param effect The effect to push.
         */
        void push(std::unique_ptr<effects::IOneShotEffect> &&effect)
        {
            m_stack.push_back(std::move(effect));
        }

        /** Resolves the next effect in the stack and pops it from the stack.
         * @param game The game instance.
         */
        void resolveNext(core::Game &game);

    private:
        std::vector<std::unique_ptr<effects::IOneShotEffect>> m_stack;
    };
} // namespace dandan::core

#endif
