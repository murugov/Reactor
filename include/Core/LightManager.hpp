#ifndef LIGHT_MANAGER_HPP
#define LIGHT_MANAGER_HPP

#include <vector>

#include "Graphic/Colors.hpp"
#include "Math/Vector.hpp"

namespace Core {

struct Light {
    Math::Vector3D pos;
    Color color = Graphic::Colors::White;
    bool enabled = true;
};

// NOTE: Ideally, we should put the light sources in a separate class and accurately implement the apply method for lights_
class LightManager {
private:
    std::vector<Light> lights_ {};

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

    void addLight (const Light& light);
    void setAllEnabled (bool state);
    void clear ();
};

} // namespace Core

#endif