#ifndef MANAABILITY_H
#define MANAABILITY_H

#include "IAbility.h"
#include <nlohmann/json.hpp>
#include <iostream>

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

    std::string_view ManaTypeToString(ManaType type) const
    {
        switch (type)
        {
        case COLORLESS:
            return "Colorless";
        case WHITE:
            return "White";
        case BLUE:
            return "Blue";
        case BLACK:
            return "Black";
        case RED:
            return "Red";
        case GREEN:
            return "Green";
        default:
            return "Unknown";
        }
    }

    void resolve() override
    {
        std::cout << "Resolving ManaAbility\n";
        std::cout << "Adding mana " << ManaTypeToString(m_color) << " to mana pool\n";
    }

    void from_json(const nlohmann::json &j, IAbility &ability) override
    {
        auto &manaAbility = dynamic_cast<ManaAbility &>(ability);
        manaAbility.m_color = j.at("color").get<ManaType>();
    }

    void to_json(nlohmann::json &j, const IAbility &ability) override
    {
        const auto &manaAbility = dynamic_cast<const ManaAbility &>(ability);
        j = nlohmann::json{{"color", manaAbility.m_color}};
    }

private:
    ManaType m_color{COLORLESS};
};

#endif