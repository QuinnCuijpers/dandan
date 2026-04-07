#ifndef MANAABILITY_H
#define MANAABILITY_H

#include "IAbility.h"

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
        ManaAbility(ManaType color) : m_color(color)
        {
        }

        std::string_view ManaTypeToString(ManaType type) const;

        static ManaType ManaTypeFromString(const std::string_view &str);

        ManaType getColor() const
        {
            return m_color;
        }

        void resolve() override;

    private:
        ManaType m_color{COLORLESS};
    };
} // namespace dandan::abilities

#endif