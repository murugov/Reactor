#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Graphic/SpriteMaterial.hpp"
#include "Math/Transform.hpp"

namespace Graphic {

class Canvas {
private:
    Math::Transform2D transform_;
    SpriteMaterial material_;
    
public:
    // -------------------------------------------------------------------------------
    // --- Constructors ---

    Canvas(Math::Vector2D pos, int width, int height)
          : transform_{pos, {static_cast<float>(width), static_cast<float>(height)}, 1.0f, 0.0f}
          , material_() {}

    Canvas(Math::Vector2D pos, int width, int height, Color color, float scale = 1.0f)
          : transform_{pos, {static_cast<float>(width), static_cast<float>(height)}, scale, 0.0f}
          , material_(color) {}

    Canvas(Math::Vector2D pos, int width, int height, SpriteMaterial&& material, float scale = 1.0f)
          : transform_{pos, {static_cast<float>(width), static_cast<float>(height)}, scale, 0.0f}
          , material_(std::move(material)) {}

    // --- Copy Semantics Disabled ---

    Canvas(const Canvas& other) = delete;
    Canvas& operator=(const Canvas& other) = delete;

    // --- Move Semantics ---
    
    Canvas(Canvas&& other) noexcept = default;
    Canvas& operator=(Canvas&& other) noexcept = default;

    ~Canvas() = default;
    
    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    Math::Vector2D pos()     const { return transform_.position; }
    float          x()       const { return transform_.position.x(); }
    float          y()       const { return transform_.position.y(); }
    Math::Vector2D size()    const { return transform_.size; }
    int            width()   const { return static_cast<int>(transform_.size.x()); }
    int            height()  const { return static_cast<int>(transform_.size.y()); }
    float          scale()   const { return transform_.scale; }
    
    const SpriteMaterial& material() const { return material_; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void draw(float rotation_angle = 0.0f) const;
};

} // namespace Graphic

#endif
