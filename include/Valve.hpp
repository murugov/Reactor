#include "GameObject.hpp"
#include "Adapter.hpp"
#include "Vector.hpp"

namespace Graphic {
    
class Valve : public GameObject {
private:    
    float rotation_angle_ = 0.0f;  // Local rotation angle
    float rotation_speed_ = 90.0f; // Velocity of rotation

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    Valve(Math::Vector2D pos, const Canvas& canvas) 
        : GameObject(pos, canvas)
    {
        setPosition(pos);
    }

    // --- Virtual Destructor ---
    
    ~Valve() override = default;

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void update (float dt) override;
    void draw () const override;
};

}
