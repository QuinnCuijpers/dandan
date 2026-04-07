#ifndef IABILITY_H
#define IABILITY_H

#include <nlohmann/json_fwd.hpp>

namespace dandan::abilities
{
    class IAbility
    {
    public:
        virtual ~IAbility() = default;
        virtual void resolve() = 0;
    };
}; // namespace dandan::abilities

#endif