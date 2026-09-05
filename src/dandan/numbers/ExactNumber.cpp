
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/INumber.h"

namespace dandan::numbers
{
    ExactNumber::ExactNumber(int value) : m_value(value)
    {
    }

    [[nodiscard]] int ExactNumber::getValue() const
    {
        return m_value;
    }

    [[nodiscard]] int ExactNumber::getValue(
        [[maybe_unused]] core::ExecutionContext exec_ctx,
        [[maybe_unused]] effects::EffectContext context) const
    {
        return m_value;
    }

    [[nodiscard]] std::unique_ptr<INumber> ExactNumber::clone() const
    {
        return std::make_unique<ExactNumber>(m_value);
    }
} // namespace dandan::numbers
