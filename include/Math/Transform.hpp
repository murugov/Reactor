#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Math/Vector.hpp"

namespace Math {

struct Transform2D {
    Vector2D pos;
    Vector2D size;
    float scale = 1.0f;
    float rotation = 0.0f;
};

} // namespace Math

#endif
