#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include <vector>
#include <memory>
#include "Core/GameObject.hpp"

namespace Core {

class PhysicsEngine {
public:
    // -------------------------------------------------------------------------------
    // --- Deleted Constructor ---
    
    PhysicsEngine () = delete;

    // -------------------------------------------------------------------------------
    // --- Static Methods Prototypes ---
    
    static void resolveCircleCircle (Core::GameObject& obj1, Core::GameObject& obj2);
    static void resolveSquareSquare (Core::GameObject& obj1, Core::GameObject& obj2);
    static void resolveSquareCircle (Core::GameObject& obj1, Core::GameObject& obj2);
    
    static void collideObjects (std::vector<std::unique_ptr<GameObject>>& objects);
    static void collideWithWalls (std::vector<std::unique_ptr<GameObject>>& objects, 
                                 float x_min, float x_max, float y_min, float y_max);
};

} // namespace Gameplay
#endif
