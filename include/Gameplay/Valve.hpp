#ifndef VALVE_HPP
#define VALVE_HPP

#include "Core/GameObject.hpp"
#include "Graphic/Colors.hpp"
#include "Graphic/Texture.hpp"
#include "Math/Vector.hpp"

namespace Gameplay {
    
class Valve : public Core::GameObject {
private:    
    Graphic::Color color_;
    const Graphic::Texture* texture_;
    
    float rotation_angle_;  // Local rotation angle
    float rotation_speed_;  // Velocity of rotation

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    Valve(Math::Vector2D pos,
            const Graphic::Texture& texture,
            bool state = true,
            Graphic::Color color = Graphic::Colors::White,
            float start_angle = 0.0f,
            float speed = 90.0f)
        : GameObject(pos, state),
            texture_(&texture),
            color_(color),
            rotation_angle_(start_angle),
            rotation_speed_(speed)
    {}

    // --- Virtual Destructor ---
    
    ~Valve() override = default;

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void update (float dt) override;
    void draw () const override;
};

} // namespace Gameplay

#endif