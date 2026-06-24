#ifndef DANDAN_INUMBER_H
#define DANDAN_INUMBER_H

#include "dandan/core/Context.h"
#include "dandan/core/Game.h"
#include "dandan/effects/EffectContext.h"

namespace dandan::numbers
{
    class INumber
    {
    public:
        INumber() = default;
        INumber(const INumber &) = delete;
        INumber(INumber &&) = delete;
        INumber &operator=(const INumber &) = delete;
        INumber &operator=(INumber &&) = delete;
        virtual ~INumber() = default;

        [[nodiscard]] virtual int getValue(
            core::Game &game, effects::EffectContext context) const = 0;

        [[nodiscard]] virtual std::unique_ptr<INumber> clone() const = 0;
    };
} // namespace dandan::numbers

#endif