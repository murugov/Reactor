#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Colors.hpp"
#include "Texture.hpp"
#include "Vector.hpp"

namespace Graphic {

class Canvas {
private:
    Math::Vector2D pos_;
    Math::Vector2D size_;
    float scale_;
    Color color_;
    const Texture* texture_ = nullptr;          // NOTE: Maybe it needs to be a lvalue reference
    
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Canvas(const Math::Vector2D& pos, int width = 0, int height = 0, Color color = Colors::White, const Texture& texture = Texture())
          : pos_(pos), size_{ static_cast<float>(width), static_cast<float>(height) }, scale_(1.0f), color_(color), texture_(&texture) {}
          
    Canvas(const Math::Vector2D& pos, int width = 0, int height = 0, float scale = 1.0f, Color color = Colors::White, const Texture& texture = Texture())
          : pos_(pos), size_{ static_cast<float>(width), static_cast<float>(height) }, scale_(scale), color_(color), texture_(&texture) {}

    // --- Copy Semantics ---
    
    Canvas(const Canvas& other) = default;
    Canvas& operator=(const Canvas& other) = default;

    // --- Move Semantics ---
    
    Canvas(Canvas&& other) noexcept = default;
    Canvas& operator=(Canvas&& other) noexcept = default;

    ~Canvas() = default;
    
    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    Math::Vector2D pos()     const { return pos_; }
    float          x()       const { return pos_.x(); }
    float          y()       const { return pos_.y(); }
    Math::Vector2D size()    const { return size_; }
    int            width()   const { return static_cast<int>(size_.x()); }
    int            height()  const { return static_cast<int>(size_.y()); }
    float          scale()   const { return scale_; }
    Color          color()   const { return color_; }
    const Texture* texture() const { return texture_; }

    // -------------------------------------------------------------------------------
    // --- Methods ---
    
    void draw (float rotation_angle = 0.0f) const;
};

}

#endif