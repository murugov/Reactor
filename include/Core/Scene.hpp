#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory> 
#include "Core/GameObject.hpp"
#include "Graphic/Camera.hpp"
#include "Graphic/Canvas.hpp"

namespace Core {

struct Light {                      // NOTE: Ideally, we should put the light sources in a separate class and accurately implement the apply method for lights_
    Math::Vector3D pos;
    Color color = Graphic::Colors::White;
    bool enabled = true;
};
    
class Scene {       // FIXME: Remove lights_ and add LightManager
private:
    Graphic::Canvas background_canvas_;
    std::vector<std::unique_ptr<GameObject>> objects_{};
    std::vector<Light> lights_{};

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Scene(Graphic::Canvas background)                                        // TODO: Add color setting
        : background_canvas_(std::move(background)) {}
    
    // --- Destructor ---

    ~Scene() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    const Graphic::Canvas& background() const { return background_canvas_; }
    Graphic::Canvas& background()             { return background_canvas_; }
    
    const std::vector<std::unique_ptr<GameObject>>& objects() const { return objects_; }
    const std::vector<Light>& lights()                        const { return lights_; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void bind (const Graphic::Camera& camera) const;
    void unbind (const Graphic::Camera& camera) const;

    void addObject (std::unique_ptr<GameObject> obj);
    void addLight (const Light& obj);

    void setAllObjects (bool state);
    void setAllLights  (bool state);

    void draw () const;
    void clear ();
};

} // namespace Core

#endif