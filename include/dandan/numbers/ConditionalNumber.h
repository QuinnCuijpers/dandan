#ifndef DANDAN_CONDITIONALNUMBER_H
#define DANDAN_CONDITIONALNUMBER_H

#include "dandan/conditions/ICondition.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/INumber.h"
#include <memory>
namespace dandan::numbers
{
    class ConditionalNumber : public INumber
    {

    public:
        ConditionalNumber(std::unique_ptr<INumber> if_,
                          std::unique_ptr<INumber> else_,
                          std::unique_ptr<conditions::ICondition> &&condition)
            : m_if_number{std::move(if_)}, m_else_number(std::move(else_)),
              m_condition{std::move(condition)}
        {
        }
        ConditionalNumber(int if_, int else_,
                          std::unique_ptr<conditions::ICondition> &&condition)
            : m_if_number{std::make_unique<ExactNumber>(if_)},
              m_else_number(std::make_unique<ExactNumber>(else_)),
              m_condition{std::move(condition)}
        {
        }

        int getValue(core::Game &game,
                     effects::EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<INumber> clone() const override
        {
            return std::make_unique<ConditionalNumber>(m_if_number->clone(),
                                                       m_else_number->clone(),
                                                       m_condition->clone());
        }

        [[nodiscard]] const INumber *getIfNumber() const
        {
            return m_if_number.get();
        }

        [[nodiscard]] const INumber *getElseNumber() const
        {
            return m_else_number.get();
        }

        [[nodiscard]] const conditions::ICondition *getCondition() const
        {
            return m_condition.get();
        }

    private:
        std::unique_ptr<INumber> m_if_number;
        std::unique_ptr<INumber> m_else_number;
        std::unique_ptr<conditions::ICondition> m_condition;
    };
} // namespace dandan::numbers

#endif