#include "LightManager.hpp"

namespace Graphic {
    
// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void LightManager::addLight(const Math::Vector3D& pos, Color color) {
    lights_.push_back({pos, true, color});
}

void LightManager::clear() {
    lights_.clear();
}

void LightManager::setAllEnabled(bool state) {
    for (auto& light : lights_) {
        light.enabled = state;
    }
}

Light& LightManager::getLightRef(size_t index) {
    return lights_[index];
}

}