#ifndef SCENE_HPP
#define SCENE_HPP

#include "Canvas.hpp"
#include "LightManager.hpp"
#include "Camera.hpp"

namespace Graphic {

class Scene {
private:
    Canvas background_canvas_;
    std::vector<Canvas> objects_;
    LightManager lightManager_;

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Scene(Canvas background) 
        : background_canvas_(std::move(background)), lightManager_() {}
    
    // --- Destructor ---

    ~Scene() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    const Canvas& background() const { return background_canvas_; }
    Canvas& background()             { return background_canvas_; }
    
    const LightManager& lightManager() const { return lightManager_; }
    LightManager& lightManager()             { return lightManager_; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void bind (const Camera& camera) const;
    void unbind (const Camera& camera) const;

    void add_object(Canvas obj);
    void draw() const;
};

}

#endif