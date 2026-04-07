#ifndef DANDAN_GENERICMANACOST_H
#define DANDAN_GENERICMANACOST_H

#include "ICost.h"

namespace dandan::costs
{
    class GenericManaCost : public ICost
    {
    public:
        explicit GenericManaCost(int amount) : m_amount{amount} {};

        int getAmount() const
        {
            return m_amount;
        }

        void evaluate() override;

    private:
        int m_amount{2};
    };
} // namespace dandan::costs

#endif