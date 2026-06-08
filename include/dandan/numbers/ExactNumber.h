#ifndef DANDAN_EXACTNUMBER_H
#define DANDAN_EXACTNUMBER_H

#include "dandan/numbers/INumber.h"

namespace dandan::numbers
{
    class ExactNumber : public INumber
    {
    public:
        explicit ExactNumber(int value) : m_value(value)
        {
        }

        [[nodiscard]] int getValue() const
        {
            return m_value;
        }

        [[nodiscard]] int getValue(
            [[maybe_unused]] core::Game &game) const override
        {
            return m_value;
        }

        [[nodiscard]] std::unique_ptr<INumber> clone() const override
        {
            return std::make_unique<ExactNumber>(m_value);
        }

    private:
        int m_value;
    };
} // namespace dandan::numbers

#endif