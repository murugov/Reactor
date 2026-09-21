#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

namespace Graphic {
    
class GameObject {
public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---
    
    GameObject() = default;
    
    // --- Virtual Distructor ---
    
    virtual ~GameObject() = default;

    // -------------------------------------------------------------------------------
    // --- Pure Virtual Functions ---
    
    virtual void update (float /*dt*/) {}
    virtual void draw () const = 0;         
};
}

#endif