#ifndef CHEMICAL_ENGINE_HPP
#define CHEMICAL_ENGINE_HPP

#include <vector>
#include <memory>
#include "Core/GameObject.hpp"

namespace Core {

class ChemicalEngine {
public:
    // -------------------------------------------------------------------------------
    // --- Deleted Constructor ---
    
    ChemicalEngine () = delete;

    // -------------------------------------------------------------------------------
    // --- Static Methods Prototypes ---

    static void processReactions (std::vector<std::unique_ptr<Core::GameObject>>& objects);

    static void reactCircleCircle (Core::GameObject& circle1, Core::GameObject& circle2, 
                                  std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue);

    static void reactCircleSquare (Core::GameObject& circle, Core::GameObject& square, 
                                  std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue);
    
    static void reactSquareCircle(Core::GameObject& square, Core::GameObject& circle, 
                                  std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue);
    
    static void reactSquareSquare (Core::GameObject& square1, Core::GameObject& square2, 
                                  std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue);
};

} // namespace Core

#endif
