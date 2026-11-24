#ifndef DANDAN_INUMBER_H
#define DANDAN_INUMBER_H

#include "dandan/core/ExecutionContext.h"
#include "dandan/effects/EffectContext.h"

namespace dandan::numbers
{
    /** @brief Interface for values computed from the current game state.
     * @class INumber
     */
    class INumber
    {
    public:
        INumber() = default;
        INumber(const INumber &) = delete;
        INumber(INumber &&) = delete;
        INumber &operator=(const INumber &) = delete;
        INumber &operator=(INumber &&) = delete;
        virtual ~INumber() = default;

        /** Evaluates the number.
         * @param exec_ctx The execution context.
         * @param context The effect context.
         * @return The evaluated number.
         */
        [[nodiscard]] virtual int getValue(
            core::ExecutionContext exec_ctx,
            effects::EffectContext context) const = 0;

        /** Creates a copy of the number expression.
         * @return A unique pointer to the cloned number.
         */
        [[nodiscard]] virtual std::unique_ptr<INumber> clone() const = 0;
    };
} // namespace dandan::numbers

#endif
