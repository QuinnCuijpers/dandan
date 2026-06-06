#ifndef DANDAN_CORE_STACK_H
#define DANDAN_CORE_STACK_H

#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <variant>
#include <vector>

namespace dandan::core
{

    using StackObject = std::variant<CardID, abilities::BoundAbility>;

    /** @brief The class that represents the stack that holds effects that
     * are about to `apply`
     * @class Stack
     */
    class Stack
    {
    public:
        Stack() = default;

        /** Pushes a StackObject onto the stack.
         * @param object The object to push.
         */
        void push(const StackObject &object)
        {
            std::cout << "Pushing object onto stack\n";
            m_stack.push_back(object);
        }

        StackObject pop()
        {
            if (m_stack.empty())
            {
                throw std::runtime_error("Cannot pop from an empty stack");
            }
            auto object = m_stack.back();
            m_stack.pop_back();
            return object;
        }

        /** Checks if the stack is empty.
         * @return True if the stack is empty, false otherwise.
         */
        [[nodiscard]] bool isEmpty() const
        {
            return m_stack.empty();
        }

        /** Resolves the next object in the stack and pops it from the stack.
         * @param game The game instance.
         */
        void resolveNext(core::Game &game);

        /** Gets the stack objects immutably.
         * @return A const reference to the vector of stack objects.
         */
        [[nodiscard]] const std::vector<StackObject> &getStackObjects() const
        {
            return m_stack;
        }

    private:
        std::vector<StackObject> m_stack;
    };
} // namespace dandan::core

#endif
