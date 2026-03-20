#ifndef IABILITY_H
#define IABILITY_H

#include <nlohmann/json_fwd.hpp>

class IAbility
{
public:
    virtual ~IAbility() = default;
    virtual void resolve() = 0;

    virtual void from_json(const nlohmann::json &j, IAbility &ability) = 0;
    virtual void to_json(nlohmann::json &j, const IAbility &ability) = 0;
};

#endif