#ifndef TEMPERATURE_CONTROLLER_HPP
#define TEMPERATURE_CONTROLLER_HPP

#include "Core/GameObject.hpp"
#include "Graphic/SpriteMaterial.hpp"
#include "Math/Vector.hpp"

namespace Gameplay {
    
class TemperatureController : public Core::GameObject {
private:    
    Graphic::SpriteMaterial material_;
    Math::Vector2D size_;
    float rotation_angle_;  // Local rotation angle

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    TemperatureController (Math::Vector2D pos,
          Graphic::SpriteMaterial&& material,
          Math::Vector2D size,
          bool state = true,
          float start_angle = 0.0f,
          Math::Vector2D vel = { 0.0f, 0.0f })
        : GameObject(pos, vel, -1.0f, state),
          material_(std::move(material)),
          size_(size),
          rotation_angle_(start_angle)
    {}

    // --- Virtual Destructor ---
    
    ~TemperatureController () override = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    float rotation_angle() const override { return rotation_angle_; }
    
    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void update (float /*dt*/) override;
    void draw () const override;

    Core::ObjectType getObjectType () const override { return Core::ObjectType::TemperatureController; }
    Core::HitboxType getHitboxType () const override { return Core::HitboxType::None; };
};

} // namespace Gameplay

#endif