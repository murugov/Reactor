#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "Math/Vector.hpp"

namespace Math {

struct Rectangle {
    Math::Vector2D pos;
    Math::Vector2D size;
};

struct Circle {
    Math::Vector2D pos;
    float radius;
};

struct Triangle {
    Math::Vector2D v1;
    Math::Vector2D v2;
    Math::Vector2D v3;
};

} // namespace Math

#endif
