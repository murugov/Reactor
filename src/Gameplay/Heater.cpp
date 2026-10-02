#include "Gameplay/Heater.hpp"

namespace Gameplay {

// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

void Heater::draw() const {
    Math::Transform2D transform {};
    transform.pos      = pos_;           
    transform.size     = size_;          
    transform.rotation = 0.0f;

    material_.draw(transform);
}

} // namespace Gameplay
