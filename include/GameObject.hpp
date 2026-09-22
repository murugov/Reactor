#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "Canvas.hpp"
#include "Vector.hpp"

namespace Graphic {
    
class GameObject {
protected:
    Math::Vector2D pos_{};
    const Canvas& canvas_;
    bool enabled_ = true;
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    GameObject(Math::Vector2D pos, const Canvas& canvas) : pos_(pos), canvas_(canvas) {}
    
    // --- Virtual Distructor ---
    
    virtual ~GameObject() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    Math::Vector2D getPosition () const { return pos_; }
    bool isEnabled ()             const { return enabled_; }
    Canvas getCanvas ()           const { return canvas_; }

    // -------------------------------------------------------------------------------
    // --- Setters ---
    
    void setPosition (const Math::Vector2D& pos) { pos_ = pos; }
    void setEnabled (bool enabled)               { enabled_ = enabled; }

    // FIXME: Move semantics are not supported here
    // void setCanvas (const Canvas& canvas)        { canvas_ = canvas; }
    
    // -------------------------------------------------------------------------------
    // --- Pure Virtual Functions ---
    
    virtual void update (float /*dt*/) {}
    virtual void draw () const = 0;         
};
}

#endif