#ifndef CHEMICAL_ENGINE_HPP
#define CHEMICAL_ENGINE_HPP

#include <vector>
#include <memory>
#include "Core/GameObject.hpp"

namespace Core {

class ChemicalEngine {
private:

    // -------------------------------------------------------------------------------
    // --- Static Methods Prototypes ---
    
    static void reactCircleCircle(Core::GameObject& c1, Core::GameObject& c2, 
                                  std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue);
    
    static void reactSquareCircle(Core::GameObject& square, Core::GameObject& circle, 
                                  std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue);
    
    static void reactSquareSquare(Core::GameObject& s1, Core::GameObject& s2, 
                                  std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue);

    static bool checkIntersection(const Core::GameObject& obj1, const Core::GameObject& obj2);

public:
    static void processReactions(std::vector<std::unique_ptr<Core::GameObject>>& objects);
};

} // namespace Core

#endif
