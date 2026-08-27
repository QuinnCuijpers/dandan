#ifndef DANDAN_GRAVEYARDCOUNT_H
#define DANDAN_GRAVEYARDCOUNT_H

#include "dandan/effects/EffectContext.h"
#include "dandan/numbers/INumber.h"

namespace dandan::numbers
{
    class GraveyardCount : public INumber
    {
    public:
        explicit GraveyardCount(std::string name);

        [[nodiscard]] const std::string &getName() const;

        [[nodiscard]] int getValue(
            core::ExecutionContext exec_ctx,
            [[maybe_unused]] effects::EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<INumber> clone() const override;

    private:
        std::string m_name;
    };
} // namespace dandan::numbers

#endif // DANDAN_GRAVEYARDCOUNT_H
