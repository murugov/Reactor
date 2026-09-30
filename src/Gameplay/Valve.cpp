#include "Gameplay/Valve.hpp"
#include "Graphic/Adapter.hpp"

namespace Gameplay {

    void Valve::update(float dt) {
        if (Graphic::Adapter::isMouseButtonPressed(1)) { // FIXME: Add button keys
            Math::Vector2D mouse_pos = Graphic::Adapter::getMousePosition();
    
            // hitbox (AABB)
            float scaled_width  = size_.x() * scale_;
            float scaled_height = size_.y() * scale_;
    
            // AABB colision
            bool hit_x = (mouse_pos.x() >= pos_.x()) && (mouse_pos.x() <= pos_.x() + scaled_width);
            bool hit_y = (mouse_pos.y() >= pos_.y()) && (mouse_pos.y() <= pos_.y() + scaled_height);
    
            if (hit_x && hit_y) {
                if (rotation_speed_ == 0.0f) {
                    rotation_speed_ = 120.0f;
                } else {
                    rotation_speed_ = 0.0f;
                }
            }
        }
    
        if (rotation_speed_ != 0.0f) {
            rotation_angle_ += rotation_speed_ * dt;
            if (rotation_angle_ >= 360.0f) {
                rotation_angle_ -= 360.0f;
            }
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
