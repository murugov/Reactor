#ifndef CIRCLE_MOLECULE_HPP
#define CIRCLE_MOLECULE_HPP

#include "Graphic/Colors.hpp"
#include "Core/GameObject.hpp"
#include "Math/Vector.hpp"

namespace Gameplay {

class CircleMolecule : public Core::GameObject {
private:
    float radius_;
    Graphic::Color color_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    CircleMolecule (Math::Vector2D pos, Math::Vector2D vel, float radius, Graphic::Color color, bool state = true)
        : GameObject (pos, vel, (3.1415f * radius * radius), state), radius_(radius), color_(color) {}

    // --- Destructor ---
    
    ~CircleMolecule () override = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    float radius () const { return radius_; }

    // -------------------------------------------------------------------------------
    // --- Setters ---

    void setRadius (float radius) { radius_ = radius; }
    
    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void update (float dt) override;
    void draw () const override;

    Core::HitboxType getHitboxType () const override { return Core::HitboxType::Circle; };
};

} // namespace Gameplay

#endif
