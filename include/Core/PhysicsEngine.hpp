#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include <vector>
#include <memory>
#include "Core/GameObject.hpp"
#include "Gameplay/CircleMolecule.hpp"
#include "Gameplay/SquareMolecule.hpp"

namespace Core {

class PhysicsEngine {
private:
    static void resolveCircleCircle (Gameplay::CircleMolecule& circle1, Gameplay::CircleMolecule& circle2);
    static void resolveSquareSquare (Gameplay::SquareMolecule& square1, Gameplay::SquareMolecule& square2);
    static void resolveSquareCircle (Gameplay::SquareMolecule& square,  Gameplay::CircleMolecule& circle);
    
public:
    // -------------------------------------------------------------------------------
    // --- Deleted Constructor ---
    
    PhysicsEngine () = delete;

    // -------------------------------------------------------------------------------
    // --- Static Methods Prototypes ---
    
    static void collideObjects (std::vector<std::unique_ptr<GameObject>>& objects);

    static void collideWithWalls (std::vector<std::unique_ptr<GameObject>>& objects, 
                                 float x_min, float x_max, float y_min, float y_max);
};

} // namespace Gameplay
#endif
