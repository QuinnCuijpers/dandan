#ifndef DANDAN_CONDITIONALNUMBER_H
#define DANDAN_CONDITIONALNUMBER_H

#include "dandan/conditions/ICondition.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/numbers/INumber.h"
#include <memory>

namespace dandan::numbers
{
    class ConditionalNumber : public INumber
    {

    public:
        ConditionalNumber(std::unique_ptr<INumber> if_,
                          std::unique_ptr<INumber> else_,
                          std::unique_ptr<conditions::ICondition> condition);

        ConditionalNumber(int if_, int else_,
                          std::unique_ptr<conditions::ICondition> condition);

        int getValue(core::Game &game,
                     effects::EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<INumber> clone() const override;

        [[nodiscard]] const INumber *getIfNumber() const;

        [[nodiscard]] const INumber *getElseNumber() const;

        [[nodiscard]] const conditions::ICondition *getCondition() const;

    private:
        std::unique_ptr<INumber> m_if_number;
        std::unique_ptr<INumber> m_else_number;
        std::unique_ptr<conditions::ICondition> m_condition;
    };
} // namespace dandan::numbers

#endif
