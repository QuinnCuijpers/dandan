#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include <iostream>

namespace dandan::effects
{
    void AttackPreventionEffect::check()
    {
        std::cout << "Attack prevention check executed.\n";
    }

} // namespace dandan::effects