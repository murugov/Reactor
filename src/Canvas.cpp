#include "Canvas.hpp"
#include "Adapter.hpp"
#include "Vector.hpp"

namespace Graphic {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---
    
void Canvas::draw(float rotation_angle) const {
    if (texture_ && texture_->is_loaded()) {
        Math::Vector2D centered_pos = pos_ - (size_ * scale_) / 2.0f;

        Adapter::drawTexture (*texture_, centered_pos, color_, scale_, rotation_angle);
    } 
    else {
        Adapter::drawRectangle (*this, pos_, size_,color_);
    }
}

}