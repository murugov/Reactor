#include "Gameplay/Valve.hpp"
#include "Graphic/Adapter.hpp"

namespace Gameplay {

// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---
    
void Valve::update(float dt) {
    if (Graphic::Adapter::isMouseButtonPressed(1)) { // FIXME: Add button keys
        Math::Vector2D mouse_pos = Graphic::Adapter::getMousePosition();

        float scaled_width  = size_.x() * scale_;
        float scaled_height = size_.y() * scale_;

        bool hit_x = (mouse_pos.x() >= pos_.x()) && (mouse_pos.x() <= pos_.x() + scaled_width);
        bool hit_y = (mouse_pos.y() >= pos_.y()) && (mouse_pos.y() <= pos_.y() + scaled_height);

        if (hit_x && hit_y) {
            is_open_ = !is_open_;
        }
    }

    float target_angle = is_open_ ? -120.0f : 0.0f;

    if ((rotation_angle_ > target_angle) && is_open_) {        
        rotation_angle_ -= rotation_speed_ * dt;
    }
    else if ((rotation_angle_ < target_angle) && !is_open_) {        
        rotation_angle_ += rotation_speed_ * dt;
    }
}

void Valve::draw() const {
    Math::Transform2D transform {};
    transform.pos      = pos_;
    transform.size     = size_;          
    transform.scale    = scale_;         
    transform.rotation = rotation_angle_; 

    material_.draw(transform); 
}

} // namespace Gameplay
