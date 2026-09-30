#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <raylib.h>
#include "Math/Vector.hpp"

namespace Graphic {

class Camera {
private:
    ::Camera2D raw_camera_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---

    Camera(Math::Vector2D world_target, Math::Vector2D screen_offset, float zoom = 1.0, float rotation = 0.0) {
        raw_camera_.target   = ::Vector2{ world_target.x(),  world_target.y() };
        raw_camera_.offset   = ::Vector2{ screen_offset.x(), screen_offset.y() };
        raw_camera_.zoom     = zoom;
        raw_camera_.rotation = rotation;
    }

    // --- Destructor ---

    ~Camera() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    ::Camera2D getRaw () const { return raw_camera_; }

    Math::Vector2D target() const { return Math::Vector2D{ raw_camera_.target.x, raw_camera_.target.y }; }
    float zoom() const { return raw_camera_.zoom; }

    // -------------------------------------------------------------------------------
    // --- Setters ---

    void setTarget (const Math::Vector2D& new_target) { raw_camera_.target = ::Vector2{ new_target.x(), new_target.y() }; }
    void setZoom (float zoom) { raw_camera_.zoom = zoom; }
    void setRotation (float rotation) { raw_camera_.rotation = rotation; }
    
    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---

    void begin () const;
    void end () const;
    void lookAt (const Math::Vector2D& world_pos);
};

} // namespace Graphic

#endif
