#ifndef VALVE_HPP
#define VALVE_HPP

#include "Core/GameObject.hpp"
#include "Graphic/SpriteMaterial.hpp"
#include "Math/Vector.hpp"

namespace Gameplay {
    
class Valve : public Core::GameObject {
private:    
    Graphic::SpriteMaterial material_;
    Math::Vector2D size_;
    float rotation_angle_;  // Local rotation angle
    float rotation_speed_;  // Velocity of rotation
    bool is_open_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    Valve (Math::Vector2D pos,
          Graphic::SpriteMaterial&& material,
          Math::Vector2D size,
          bool state = true,
          float start_angle = 0.0f,
          float speed = 90.0f,
          bool is_open = false,
          Math::Vector2D vel = { 0.0f, 0.0f })
        : GameObject(pos, vel, -1.0f, state),
          material_(std::move(material)),
          size_(size),
          rotation_angle_(start_angle),
          rotation_speed_(speed),
          is_open_(is_open)
    {}

    // --- Virtual Destructor ---
    
    ~Valve () override = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    bool isOpen () const { return is_open_; }

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void update (float dt) override;
    void draw () const override;

    Core::ObjectType getObjectType () const override { return Core::ObjectType::Valve; }
    Core::HitboxType getHitboxType () const override { return Core::HitboxType::None; };
};

} // namespace Gameplay

#endif