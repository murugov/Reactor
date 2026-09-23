#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "Math/Vector.hpp"

namespace Core {
    
class GameObject {
protected:
    Math::Vector2D pos_;
    bool enabled_;
    
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    GameObject(Math::Vector2D pos, bool state = true) : pos_(pos), enabled_(state) {}
    
    // --- Virtual Distructor ---
    
    virtual ~GameObject() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    Math::Vector2D getPosition () const { return pos_; }
    bool isEnabled ()             const { return enabled_; }

    // -------------------------------------------------------------------------------
    // --- Setters ---
    
    void setPosition (const Math::Vector2D& pos) { pos_ = pos; }
    void setEnabled (bool enabled)               { enabled_ = enabled; }
    
    // -------------------------------------------------------------------------------
    // --- Pure Virtual Methods ---
    
    virtual void update (float /*dt*/) {}
    virtual void draw () const = 0;         
};

} // namespace Core

#endif