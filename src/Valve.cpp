#include "Valve.hpp"

namespace Graphic {
    
// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

void Valve::update(float dt) {
    rotation_angle_ += rotation_speed_ * dt;
    if (rotation_angle_ >= 360.0f) rotation_angle_ -= 360.0f;
}

void Valve::draw() const {
    float scale = 1.0f; 

    float half_width  = (static_cast<float>(texture_.width())  * scale) / 2.0f;
    float half_height = (static_cast<float>(texture_.height()) * scale) / 2.0f;

    Math::Vector2D draw_pos { pos_.x() - half_width, pos_.y() - half_height };

    Adapter::drawTexture(texture_, draw_pos, Colors::White, scale, rotation_angle_);
}

}