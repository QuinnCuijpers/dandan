#ifndef DANDAN_ATTACKPREVENTIONEFFECT_H
#define DANDAN_ATTACKPREVENTIONEFFECT_H

#include "IPreventionEffect.h"

namespace dandan::effects
{
    class AttackPreventionEffect : public IPreventionEffect
    {
    public:
        void check() override;
    };

} // namespace dandan::effects

#endif // DANDAN_ATTACKPREVENTIONEFFECT_H