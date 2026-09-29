#include "Graphic/Adapter.hpp"
#include "Graphic/Canvas.hpp"
#include "Math/Vector.hpp"

namespace Graphic {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---
    
void Canvas::draw() const {
    material_.draw(this->transform_);
}

} // namespace Graphic