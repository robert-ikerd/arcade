#pragma once
#include <SDL3/SDL.h>

namespace Graphics {

    struct Color {
        uint8_t r, g, b;
    };

    namespace Colors {
        extern const Color White;
        extern const Color Gray;
        extern const Color DarkGray;
        extern const Color Black;
        extern const Color Red;
        extern const Color Crimson;
        extern const Color Pink;
        extern const Color Blue;
        extern const Color Azure;
        extern const Color Yellow;
        extern const Color Green;
        extern const Color Orange;
        extern const Color Purple;
        extern const Color Shadow;
    }
}