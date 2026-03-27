#ifndef MANAABILITY_H
#define MANAABILITY_H

#include "IAbility.h"
#include <iostream>

namespace dandan::abilities
{

    class ManaAbility : public IAbility
    {
    public:
        enum ManaType
        {
            COLORLESS,
            WHITE,
            BLUE,
            BLACK,
            RED,
            GREEN
        };

        ManaAbility() = default;
        ManaAbility(ManaType color) : m_color(color) {}

        std::string_view ManaTypeToString(ManaType type) const;

        void resolve() override;

        void from_json(const nlohmann::json &j, IAbility &ability) override;

        void to_json(nlohmann::json &j, const IAbility &ability) override;

    private:
        ManaType m_color{COLORLESS};
    };
}

#endif