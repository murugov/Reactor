#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "Math/Vector.hpp"

namespace Core {

enum class HitboxType {
    None,
    Circle,
    Square
};
    
class GameObject {
protected:
    Math::Vector2D pos_;
    Math::Vector2D velocity_;
    float mass_;
    bool enabled_;
    
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructors ---

    // NOTE: Negative mass belongs to an infinitely heavy object.
    GameObject (Math::Vector2D pos, Math::Vector2D vel = { 0.0f, 0.0f }, float mass = -1.0f, bool state = true) : pos_(pos), velocity_(vel), mass_(mass), enabled_(state) {}

    // --- Virtual Destructor ---
    
    virtual ~GameObject () = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    Math::Vector2D pos ()      const { return pos_; }
    Math::Vector2D velocity () const { return velocity_; }
    float mass ()              const { return mass_; }
    bool isEnabled ()          const { return enabled_; }

    // -------------------------------------------------------------------------------
    // --- Setters ---
    
    void setPosition (const Math::Vector2D& pos) { pos_ = pos; }
    void setVelocity (const Math::Vector2D& vel) { velocity_ = vel; }
    void setMass     (float mass)                { mass_ = mass; }    
    void setEnabled  (bool enabled)              { enabled_ = enabled; }
    
    // -------------------------------------------------------------------------------
    // --- Pure Virtual Methods ---
    
    virtual void update (float /*dt*/) {}
    virtual void draw () const = 0;        
    
    virtual HitboxType getHitboxType () const = 0;

};

} // namespace Core

#endif