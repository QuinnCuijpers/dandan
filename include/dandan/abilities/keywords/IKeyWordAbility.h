#ifndef DANDAN_IKEYWORDABILITY_H
#define DANDAN_IKEYWORDABILITY_H

#include "dandan/abilities/IAbility.h"
#include "dandan/abilities/keywords/Keyword.h"

namespace dandan::abilities
{
    class IKeyWordAbility : public IAbility
    {
    public:
        [[nodiscard]] virtual Keyword keyword() const = 0;

    private:
    };
} // namespace dandan::abilities

#endif // !DANDAN_IKEYWORDABILITY_H
