#include "Core/LightManager.hpp"

namespace Core {
    
// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void LightManager::addLight(const Light& light) {
    lights_.push_back(light);
}

void LightManager::setAllEnabled(bool state) {
    for (auto& light : lights_) {
        light.enabled = state;
    }
}

void LightManager::clear() {
    lights_.clear();
}

} // namespace Core