#ifndef MANAABILITY_H
#define MANAABILITY_H

#include "IAbility.h"

namespace dandan::abilities
{

    class ManaAbility final : public IAbility
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
        explicit ManaAbility(ManaType color) : m_color(color)
        {
        }

        static std::string_view ManaTypeToString(ManaType type);

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