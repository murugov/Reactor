#include "Scene.hpp"
#include "Adapter.hpp"
#include "GameObject.hpp"

namespace Graphic {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Scene::bind (const Camera& camera) const {
    // NOTE: Begin scissor mode (define screen area for following drawing)
    Adapter::beginScissorMode(static_cast<int>((background_canvas_.pos()).x()), static_cast<int>((background_canvas_.pos()).y()), background_canvas_.width(), background_canvas_.height());
    camera.begin();
}

void Scene::unbind (const Camera& camera) const {
    camera.end();
    Adapter::endScissorMode();
}


void Scene::addObject(std::unique_ptr<Graphic::GameObject> obj) {
    objects_.push_back(std::move(obj));
}

void Scene::addLight (const Light& light) {
    lights_.push_back(std::move(light));
}

void Scene::setAllObjects (bool state) {
    for (auto& object : objects_) {
        object->setEnabled(state);
    }
}

void Scene::setAllLights (bool state) {
    for (auto& light : lights_) {
        light.enabled = state;
    }
}

void Scene::draw () const {
    background_canvas_.draw();
    
    for (const auto& obj : objects_) {
        if (obj->isEnabled()) {
            obj->draw();
        }
    }
}

void Scene::clear () {
    objects_.clear();
    lights_.clear();
}

}