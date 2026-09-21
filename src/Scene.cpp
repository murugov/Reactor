#include "Scene.hpp"
#include "Adapter.hpp"

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


void Scene::add_object(Canvas obj) {
    objects_.push_back(std::move(obj));
}

void Scene::draw() const {
    background_canvas_.draw();
    
    for (const auto& obj : objects_) {
        obj.draw();
    }

    // lightManager_.apply(); 
}

}