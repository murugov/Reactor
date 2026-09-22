#include "Valve.hpp"

namespace Graphic {
    
// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

void Valve::update(float dt) {
    rotation_angle_ += rotation_speed_ * dt;
    if (rotation_angle_ >= 360.0f) rotation_angle_ -= 360.0f;
}

void Valve::draw() const {
    canvas_.draw(rotation_angle_);
}

}