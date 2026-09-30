#include "Core/Scene.hpp"
#include "Core/GameObject.hpp"
#include "Graphic/Adapter.hpp"

namespace Core {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Scene::bind (const Graphic::Camera& camera) const {
    // NOTE: Begin scissor mode (define screen area for following drawing)
    Graphic::Adapter::beginScissorMode({ background_canvas_.pos(), background_canvas_.size() });
    camera.begin();
}

void Scene::unbind (const Graphic::Camera& camera) const {
    camera.end();
    Graphic::Adapter::endScissorMode();
}

void Scene::addObject(std::unique_ptr<GameObject> obj) {
    objects_.push_back(std::move(obj));
}

void Scene::setAllObjects (bool state) {
    for (auto& object : objects_) {
        object->setEnabled(state);
    }
}

void Scene::update(float dt) {
    // TODO: Add updating light_manager_

    for (auto& obj : objects_) {
        if (obj && obj->isEnabled()) {
            obj->update(dt); 
        }
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
    light_manager_.clear();
}

} // namespace Core