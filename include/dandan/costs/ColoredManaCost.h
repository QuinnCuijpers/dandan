#ifndef DANDAN_COLOREDMANACOST_H
#define DANDAN_COLOREDMANACOST_H

#include "ICost.h"

namespace dandan::costs
{

    class ColoredManaCost final : public ICost
    {
    public:
        enum ManaColor
        {
            WHITE,
            BLUE,
            BLACK,
            RED,
            GREEN
        };

        explicit ColoredManaCost(ManaColor color) : m_color(color)
        {
        }

        ManaColor getColor() const
        {
            return m_color;
        }

        static std::string ManaColorToString(ManaColor color);

        static ManaColor ManaColorFromString(const std::string &colorStr);

        void evaluate() override;

    private:
        ManaColor m_color;
    };
} // namespace dandan::costs
#endif