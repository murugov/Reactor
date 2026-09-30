#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory> 
#include "Core/GameObject.hpp"
#include "Core/LightManager.hpp"
#include "Graphic/Camera.hpp"
#include "Graphic/Canvas.hpp"
#include "Graphic/Texture.hpp"

namespace Core {
    
class Scene {
private:
    Graphic::Canvas background_canvas_;
    std::vector<std::unique_ptr<GameObject>> objects_ {};
    LightManager light_manager_;

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Scene(Math::Vector2D pos, int width, int height, const std::string& texture_path)
        : background_canvas_(pos, width, height, Graphic::SpriteMaterial(Graphic::Texture(texture_path))) {}

    Scene(Math::Vector2D pos, int width, int height, Graphic::Texture&& texture)
        : background_canvas_(pos, width, height, Graphic::SpriteMaterial(std::move(texture))) {}
            
    Scene(Math::Vector2D pos, int width, int height, Graphic::Color bg_color)
        : background_canvas_(pos, width, height, Graphic::SpriteMaterial(bg_color)) {}

    Scene(Graphic::Canvas&& background) 
        : background_canvas_(std::move(background)) {}
        
    // --- Destructor ---

    ~Scene() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    const Graphic::Canvas& background() const { return background_canvas_; }
    Graphic::Canvas& background()             { return background_canvas_; }
    
    const std::vector<std::unique_ptr<GameObject>>& objects() const { return objects_; }
    const LightManager& lightManager()                        const { return light_manager_; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void bind (const Graphic::Camera& camera) const;
    void unbind (const Graphic::Camera& camera) const;

    void addObject (std::unique_ptr<GameObject> obj);
    void addLight (const Light& obj);

    void setAllObjects (bool state);
    void setAllLights  (bool state);

    void update (float dt);
    
    void draw () const;
    void clear ();
};

} // namespace Core

#endif