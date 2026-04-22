#ifndef DANDAN_TAPCOST_H
#define DANDAN_TAPCOST_H

#include "dandan/costs/ICost.h"

namespace dandan::costs
{

    class TapCost : public ICost
    {
    public:
        TapCost() = default;

        void evaluate() override;
    };
} // namespace dandan::costs

#endif