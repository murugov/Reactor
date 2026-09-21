#ifndef COLORS_HPP
#define COLORS_HPP

#include <raylib.h>

namespace Graphic {

struct Color {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;

    operator ::Color() const {
        return {r, g, b, a};
    }
};

struct Colors {
    static const Color LightGray;
    static const Color Gray;
    static const Color DarkGray;
    static const Color Yellow;
    static const Color Gold;
    static const Color Orange;
    static const Color Pink;
    static const Color Red;
    static const Color Maroon;
    static const Color Green;
    static const Color Lime;
    static const Color DarkGreen;
    static const Color SkyBlue;
    static const Color Blue;
    static const Color DarkBlue;
    static const Color Purple;;
    static const Color Violet;
    static const Color DarkPurple;
    static const Color Beige;
    static const Color Brown;
    static const Color DarkBrown;
    static const Color White;
    static const Color Black;
    static const Color Blank;
    static const Color Magenta;
};

}

#endif