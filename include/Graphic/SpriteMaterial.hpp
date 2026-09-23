#ifndef SPRITE_MATERIAL_HPP
#define SPRITE_MATERIAL_HPP

#include <variant>
#include <utility>

#include "Graphic/Colors.hpp"
#include "Graphic/Texture.hpp"
#include "Math/Vector.hpp"

namespace Graphic {

class SpriteMaterial {
private:
    std::variant<Color, Texture> data_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructors ---

    // NOTE: Magenta is used as a default color to indicate uninitialized state
    SpriteMaterial() : data_(Colors::Magenta) {}

    explicit SpriteMaterial(Color color) : data_(color) {}

    explicit SpriteMaterial(Texture&& texture) : data_(std::move(texture)) {}

    // --- Copy Semantics Disabled ---
    
    SpriteMaterial(const SpriteMaterial&) = delete;
    SpriteMaterial& operator=(const SpriteMaterial&) = delete;

    // --- Move Semantics ---
    
    SpriteMaterial(SpriteMaterial&& other) noexcept = default;
    SpriteMaterial& operator=(SpriteMaterial&& other) noexcept = default;

    // --- Destructor ---
    
    ~SpriteMaterial() = default;

    // -------------------------------------------------------------------------------
    // --- Type Checks ---
    
    bool isColor()   const { return std::holds_alternative<Color>(data_); }
    bool isTexture() const { return std::holds_alternative<Texture>(data_); }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void draw (Math::Vector2D pos, Color color = Colors::Magenta) const;

};

} // namespace Graphic

#endif
