#ifndef DANDAN_EXACTNUMBER_H
#define DANDAN_EXACTNUMBER_H

#include "dandan/effects/EffectContext.h"
#include "dandan/numbers/INumber.h"

namespace dandan::numbers
{
    class ExactNumber : public INumber
    {
    public:
        explicit ExactNumber(int value);

        [[nodiscard]] int getValue() const;

        [[nodiscard]] int getValue(
            core::ExecutionContext exec_ctx, effects::EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<INumber> clone() const override;

    private:
        int m_value;
    };
} // namespace dandan::numbers

#endif
