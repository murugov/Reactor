#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Math/Vector.hpp"

namespace Math {

struct Transform2D {
    Vector2D position {};
    Vector2D size { 1.0f, 1.0f };
    float scale = 1.0f;
    float rotation = 0.0f;
};

} // namespace Math

#endif
