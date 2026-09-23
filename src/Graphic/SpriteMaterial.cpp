#include "SpriteMaterial.hpp"
#include "Adapter.hpp"
#include "Vector.hpp"

namespace Graphic {
    
// -------------------------------------------------------------------------------
// --- Methods ---

void SpriteMaterial::draw(const Canvas& canvas, Math::Vector2D pos, Math::Vector2D size, 
                          Color color, float scale, float rotation) const {
    std::visit([&canvas, pos, size, color, scale, rotation](const auto& arg) {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, Color>) {
            Adapter::drawRectangle(canvas, pos, size, arg);
        } 
        else if constexpr (std::is_same_v<T, Graphic::Texture>) {
            if (arg.is_loaded()) {
                Adapter::drawTexture(canvas, arg, pos, color, scale, rotation);
            }
        }
    }, data_);
}

}