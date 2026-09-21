#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Vector.hpp"

namespace Math {

class Sphere {
private:
    Vector2D center_pos_;
    float radius_;

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Sphere(Vector2D center_pos, float radius)
        : center_pos_(center_pos), radius_(radius) {}

    // --- Destructor ---

    ~Sphere() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    Math::Vector2D pos()    const { return center_pos_; }
    float          x()      const { return center_pos_.x(); }
    float          y()      const { return center_pos_.y(); }
    float          radius() const { return radius_; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---

    // TODO: move, ...
};

}

#endif