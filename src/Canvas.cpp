#include "Canvas.hpp"
#include "Adapter.hpp"

namespace Graphic {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---
    
void Canvas::draw() const {
    if (bg_.texture && bg_.texture->is_loaded()) {
        Math::Vector2D centered_pos {
            pos_.x() - (static_cast<float>(width_)  * scale_) / 2.0f,
            pos_.y() - (static_cast<float>(height_) * scale_) / 2.0f
        };

        Adapter::drawTexture(*bg_.texture, centered_pos, bg_.color, scale_, 0.0f);
    } 
    else {
        Adapter::drawRectangle(*this, pos_, { static_cast<float>(width_), static_cast<float>(height_) }, bg_.color);
    }
}

}