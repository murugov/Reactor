#ifndef LIGHT_MANAGER_HPP
#define LIGHT_MANAGER_HPP

#include <vector>

#include "Graphic/Colors.hpp"
#include "Math/Vector.hpp"

namespace Core {

struct Light {
    Math::Vector3D pos;
    bool enabled = true;
    Color color = Graphic::Colors::White;
};

class LightManager {
private:
    std::vector<Light> lights_{};

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    LightManager() = default;

    // --- Destructor ---

    ~LightManager() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    const std::vector<Light>& lights() const { return lights_; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---

    void   addLight (const Math::Vector3D& pos, Graphic::Color color = Graphic::Colors::White);
    void   clear ();
    void   setAllEnabled (bool state);
    Light& getLightRef(size_t index);
};

} // namespace Core

#endif