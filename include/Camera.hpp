#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <raylib.h>
#include "Vector.hpp"

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

    ::Camera2D get_raw () const { return raw_camera_; }

    Math::Vector2D target() const { return Math::Vector2D{ raw_camera_.target.x, raw_camera_.target.y }; }
    float zoom() const { return raw_camera_.zoom; }

    // -------------------------------------------------------------------------------
    // --- Setters ---

    void set_target(const Math::Vector2D& new_target) { raw_camera_.target = ::Vector2{ new_target.x(), new_target.y() }; }
    void set_zoom (float zoom) { raw_camera_.zoom = zoom; }
    void set_rotation (float rotation) { raw_camera_.rotation = rotation; }
    
    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---

    void begin () const;
    void end () const;
    void look_at (const Math::Vector2D& world_pos);
};

}

#endif
