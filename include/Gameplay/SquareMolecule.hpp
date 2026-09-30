#ifndef SQUARE_MOLECULE_HPP
#define SQUARE_MOLECULE_HPP

#include "Graphic/Colors.hpp"
#include "Core/GameObject.hpp"
#include "Math/Vector.hpp"

namespace Gameplay {

class SquareMolecule : public Core::GameObject {
private:
    Math::Vector2D size_;
    Graphic::Color color_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    SquareMolecule (Math::Vector2D pos, Math::Vector2D vel, Math::Vector2D size, Graphic::Color color, bool state = true)
        : GameObject (pos, vel, (size.x() * size.y()), state), color_(color) {
            size_ = size;
        }

    // --- Destructor ---
    
    ~SquareMolecule () override = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    Math::Vector2D size () const { return size_; }
    
    // -------------------------------------------------------------------------------
    // --- Setters ---

    void setSize (const Math::Vector2D& size) { size_ = size; }
    
    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void update (float dt) override;
    void draw () const override;

    Core::HitboxType getHitboxType () const override { return Core::HitboxType::Square; };
};

} // namespace Gameplay

#endif
