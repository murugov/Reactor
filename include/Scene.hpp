#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory> 
#include "Canvas.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"

namespace Graphic {

struct Light {                      // NOTE: Ideally, we should put the light sources in a separate class and accurately implement the apply method for lights_
    Math::Vector3D pos{};
    Color color = Colors::White;
    bool enabled = true;
};
    
class Scene {
private:
    Canvas background_canvas_;
    std::vector<std::unique_ptr<GameObject>> objects_;
    std::vector<Light> lights_{};

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Scene(Canvas background) 
        : background_canvas_(std::move(background)) {}
    
    // --- Destructor ---

    ~Scene() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    const Canvas& background() const { return background_canvas_; }
    Canvas& background()             { return background_canvas_; }
    
    const std::vector<std::unique_ptr<Graphic::GameObject>>& objects() const { return objects_; }
    const std::vector<Light>& lights()                                 const { return lights_; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void bind (const Camera& camera) const;
    void unbind (const Camera& camera) const;

    void addObject(std::unique_ptr<Graphic::GameObject> obj);
    void addLight (const Light& obj);

    void setAllObjects (bool state);
    void setAllLights  (bool state);

    void draw () const;
    void clear ();
};

}

#endif