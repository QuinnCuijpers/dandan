
#include "dandan/numbers/ExactNumber.h"

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
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] effects::EffectContext context) const
    {
        return m_value;
    }

    [[nodiscard]] std::unique_ptr<INumber> ExactNumber::clone() const
    {
        return std::make_unique<ExactNumber>(m_value);
    }
} // namespace dandan::numbers
