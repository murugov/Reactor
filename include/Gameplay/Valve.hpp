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
    float scale_;              
    float rotation_angle_;  // Local rotation angle
    float rotation_speed_;  // Velocity of rotation

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    Valve (Math::Vector2D pos,
          Graphic::SpriteMaterial&& material,
          float scale = 1.0f,
          bool state = true,
          float start_angle = 0.0f,
          float speed = 90.0f,
          Math::Vector2D vel = { 0.0f, 0.0f })
        : GameObject(pos, vel, state),
          material_(std::move(material)),
          size_(material_.getSize()),
          scale_(scale),
          rotation_angle_(start_angle),
          rotation_speed_(speed)
    {}

    // --- Virtual Destructor ---
    
    ~Valve () override = default;

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void update (float dt) override;
    void draw () const override;

    Core::HitboxType getHitboxType () const override { return Core::HitboxType::Circle; };
};

} // namespace Gameplay

#endif