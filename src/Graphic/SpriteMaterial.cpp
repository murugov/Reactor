#include "Graphic/SpriteMaterial.hpp"
#include "Graphic/Adapter.hpp"
#include "Math/Transform.hpp"

namespace Graphic {
    
// -------------------------------------------------------------------------------
// --- Methods ---

Math::Vector2D SpriteMaterial::getSize() const {
    return std::visit([](const auto& arg) -> Math::Vector2D {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, Texture>) {
            if (arg.is_loaded()) {
                return { static_cast<float>(arg.width()), static_cast<float>(arg.height()) };
            }
        }
        
        return { 50.0f, 50.0f }; 
    }, data_);
}

void SpriteMaterial::draw(Math::Transform2D transform) const {
    std::visit([transform](const auto& arg) {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, Color>) {
            Adapter::drawRectangle({ transform.pos, transform.size }, arg);
        } 
        else if constexpr (std::is_same_v<T, Texture>) {
            Adapter::drawTexture(arg, transform, Graphic::Colors::Magenta);
        }
    }, data_);
}

} // namespace Graphic