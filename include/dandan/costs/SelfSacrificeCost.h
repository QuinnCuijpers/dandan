#ifndef DANDAN_SELFSACRIFICECOST_H
#define DANDAN_SELFSACRIFICECOST_H

#include "dandan/costs/ICost.h"
namespace dandan::costs
{
    class SelfSacrificeCost : public ICost
    {
    public:
        void evaluate() override;
    };
} // namespace dandan::costs

#endif