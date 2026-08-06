#include "dandan/numbers/ConditionalNumber.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/numbers/ExactNumber.h"

namespace dandan::numbers
{

    ConditionalNumber::ConditionalNumber(
        std::unique_ptr<INumber> if_, std::unique_ptr<INumber> else_,
        std::unique_ptr<conditions::ICondition> condition)
        : m_if_number{std::move(if_)}, m_else_number(std::move(else_)),
          m_condition{std::move(condition)}
    {
    }

    ConditionalNumber::ConditionalNumber(
        int if_, int else_, std::unique_ptr<conditions::ICondition> condition)
        : m_if_number{std::make_unique<ExactNumber>(if_)},
          m_else_number(std::make_unique<ExactNumber>(else_)),
          m_condition{std::move(condition)}
    {
    }

    int ConditionalNumber::getValue(core::Game &game,
                                    effects::EffectContext context) const
    {
        if (m_condition->isSatisfied(game, context))
        {
            return m_if_number->getValue(game, context);
        }

        return m_else_number->getValue(game, context);
    }

    [[nodiscard]] std::unique_ptr<INumber> ConditionalNumber::clone() const
    {
        return std::make_unique<ConditionalNumber>(
            m_if_number->clone(), m_else_number->clone(), m_condition->clone());
    }

    [[nodiscard]] const INumber *ConditionalNumber::getIfNumber() const
    {
        return m_if_number.get();
    }

    [[nodiscard]] const INumber *ConditionalNumber::getElseNumber() const
    {
        return m_else_number.get();
    }

    [[nodiscard]] const conditions::ICondition *ConditionalNumber::
        getCondition() const
    {
        return m_condition.get();
    }

} // namespace dandan::numbers
