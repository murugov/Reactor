#include "Gameplay/Valve.hpp"
#include "Graphic/Adapter.hpp"

namespace Gameplay {
    
// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---
    
void Valve::update(float dt) {
    rotation_angle_ += rotation_speed_ * dt;
    if (rotation_angle_ >= 360.0f) {
        rotation_angle_ -= 360.0f;
    }
}

void Valve::draw() const {
    Math::Transform2D transform;
    transform.pos      = pos_;
    transform.size     = size_;
    transform.scale    = scale_;
    transform.rotation = rotation_angle_;

    material_.draw(transform); 
}

} // namespace Gameplay