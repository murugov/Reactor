#include "Gameplay/TemperatureController.hpp"
#include "Graphic/Adapter.hpp"

namespace Gameplay {

// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---
    
void TemperatureController::update(float /*dt*/) {
    float wheel = Graphic::Adapter::getMouseWheelMove();

    if (std::abs(wheel) > 1e-5f) {
        Math::Vector2D mouse_pos = Graphic::Adapter::getMousePosition();

        float scaled_width  = size_.x();
        float scaled_height = size_.y();

        bool hit_x = (mouse_pos.x() >= pos_.x()) && (mouse_pos.x() <= pos_.x() + scaled_width);
        bool hit_y = (mouse_pos.y() >= pos_.y()) && (mouse_pos.y() <= pos_.y() + scaled_height);

        if (hit_x && hit_y) {
            rotation_angle_ += wheel * 0.5f;
            
            if (rotation_angle_ > 90.0f) {
                rotation_angle_ = 90.0f;
            }
            if (rotation_angle_ < -90.0f) {
                rotation_angle_ = -90.0f;
            }
        }
    }
}

void TemperatureController::draw() const {
    Math::Transform2D transform {};
    transform.pos      = pos_;
    transform.size     = size_;          
    transform.rotation = rotation_angle_; 

    material_.draw(transform); 
}

} // namespace Gameplay
