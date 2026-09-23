#include "Gameplay/Valve.hpp"
#include "Graphic/Adapter.hpp"

namespace Graphic {
    
// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

void Valve::update(float dt) {
    rotation_angle_ += rotation_speed_ * dt;
    if (rotation_angle_ >= 360.0f) rotation_angle_ -= 360.0f;
}

void Valve::draw() const {
    if (texture_ && texture_->is_loaded()) {
        Math::Vector2D centered_pos = pos_ - (size_ * scale_) / 2.0f;

        Adapter::drawTexture (*texture_, centered_pos, color_, scale_, rotation_angle);
    } 
    else {
        Adapter::drawRectangle (*this, pos_, size_,color_);
    }
}

}