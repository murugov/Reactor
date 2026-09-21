#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Colors.hpp"
#include "Texture.hpp"
#include "Vector.hpp"

namespace Graphic {

struct BackGround {
    Color color;
    const Texture* texture = nullptr;
};
    
class Canvas {
private:
    Math::Vector2D pos_;
    int width_;
    int height_;
    float scale_;
    BackGround bg_;

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---
    
    Canvas(const Math::Vector2D& pos, int width, int height, BackGround bg, float scale = 1.0f)
          : pos_(pos), width_(width), height_(height), scale_(scale), bg_(bg) {}
  
    Canvas(const Math::Vector2D& pos, int width, int height, Color color, float scale = 1.0f)
          : pos_(pos), width_(width), height_(height), scale_(scale), bg_{color, nullptr} {}

    Canvas(const Math::Vector2D& pos, int width, int height, Color color, const Texture& texture, float scale = 1.0f)
          : pos_(pos), width_(width), height_(height), scale_(scale) {
              bg_.color = color;
              bg_.texture = &texture;
          }

    // --- Copy Semantics ---
    
    Canvas(const Canvas& other) = default;
    Canvas& operator=(const Canvas& other) = default;

    // --- Move Semantics ---
    
    Canvas(Canvas&& other) noexcept = default;
    Canvas& operator=(Canvas&& other) noexcept = default;

    ~Canvas() = default;
    
    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    Math::Vector2D pos()    const { return pos_; }
    float          x()      const { return pos_.x(); }
    float          y()      const { return pos_.y(); }
    int            width()  const { return width_; }
    int            height() const { return height_; }
    float          scale()  const { return scale_; }
    
    const BackGround& background() const { return bg_; }

    // -------------------------------------------------------------------------------
    // --- Methods ---
    
    void draw() const;
};

}

#endif