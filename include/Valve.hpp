#include "GameObject.hpp"
#include "Adapter.hpp"
#include "Vector.hpp"

namespace Graphic {
    
class Valve : public GameObject {
private:
    const Texture& texture_;
    Math::Vector2D pos_;
    float rotation_angle_ = 0.0f;  // Local rotation angle
    float rotation_speed_ = 90.0f; // Velocity of rotation

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---
    
    Valve(const Texture& texture, Math::Vector2D pos) : texture_(texture), pos_(pos) {}

    // --- Virtual Destructor ---
    
    ~Valve() override = default;

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void update (float dt) override;
    void draw () const override;

};

}