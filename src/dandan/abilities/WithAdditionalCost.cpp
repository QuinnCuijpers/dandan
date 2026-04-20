#include "dandan/abilities/WithAdditionalCost.h"

namespace dandan::abilities
{
    void WithAdditionalCost::resolve() const
    {
        m_cost->evaluate();
        m_ability->resolve();
    }
} // namespace dandan::abilities