#include "Graphic/Canvas.hpp"

namespace Graphic {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---
    
void Canvas::draw() const {
    material_.draw(this->transform_);
}

} // namespace Graphic