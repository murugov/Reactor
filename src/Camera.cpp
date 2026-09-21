#include "Camera.hpp"

namespace Graphic {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Camera::begin () const {
    BeginMode2D(raw_camera_);
}

void Camera::end () const {
    EndMode2D();
}

void Camera::look_at (const Math::Vector2D& world_pos) {
    raw_camera_.target = ::Vector2{ world_pos.x(), world_pos.y() };
}

}