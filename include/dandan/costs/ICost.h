#ifndef DANDAN_I_COST
#define DANDAN_I_COST

#include "dandan/abilities/IAbility.h"
#include <nlohmann/json_fwd.hpp>

namespace dandan::costs
{
    class ICost
    {
    public:
        virtual ~ICost() = default;
        virtual void evaluate() = 0;

        virtual void from_json(const nlohmann::json &j, ICost &cost) = 0;
        virtual void to_json(nlohmann::json &j, const ICost &cost) = 0;
    };
}

#endif