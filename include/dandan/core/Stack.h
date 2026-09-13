#ifndef DANDAN_CORE_STACK_H
#define DANDAN_CORE_STACK_H

#include "dandan/abilities/BoundAbility.h"
#include "dandan/core/CardID.h"
#include "dandan/core/CastContext.h"
#include <algorithm>
#include <variant>
#include <vector>

namespace dandan::core
{

    using StackObject = std::variant<CastContext, abilities::BoundAbility>;

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
        void push(const StackObject &object);

        /** Checks if the stack is empty.
         * @return True if the stack is empty, false otherwise.
         */
        [[nodiscard]] bool isEmpty() const;

        /** Resolves the next object in the stack and pops it from the stack.
         * @param game The game instance.
         */
        void resolveNext(core::ExecutionContext exec_ctx);

        /** Gets the stack objects immutably.
         * @return A const reference to the vector of stack objects.
         */
        [[nodiscard]] const std::vector<StackObject> &getStackObjects() const;

        void removeObject(const StackObject &object);

        void removeCard(CardID card_id)
        {
            m_stack.erase(
                std::remove_if(
                    m_stack.begin(), m_stack.end(),
                    [card_id](const StackObject &object)
                    {
                        return std::holds_alternative<CastContext>(object) &&
                               std::get<CastContext>(object).card_id == card_id;
                    }),
                m_stack.end());
        }

    private:
        std::vector<StackObject> m_stack;
    };
} // namespace dandan::core
#endif
