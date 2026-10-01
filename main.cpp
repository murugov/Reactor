#include "Core/Scene.hpp"
#include "Gameplay/MolecularContainer.hpp"
#include "Gameplay/Valve.hpp"
#include "Graphic/Adapter.hpp"
#include "Graphic/Camera.hpp"
#include "Graphic/SpriteMaterial.hpp"
#include "Graphic/Texture.hpp"
#include "Math/Vector.hpp"

int main() {
    const int window_width  = 800;
    const int window_height = 450;

    Graphic::Adapter::initWindow(window_width, window_height, "Reactor");
    
    Graphic::Camera main_camera(Math::Vector2D { 0.0f, 0.0f }, Math::Vector2D { 0.0f, 0.0f }, 1.0f);
    Core::Scene main_scene({ 0.0f, 0.0f }, window_width, window_height, "assets/textures/reactor.png");

    Graphic::Texture red_valve_tex("assets/textures/red_valve.png");
    Graphic::SpriteMaterial red_valve_material(std::move(red_valve_tex));
    
    Gameplay::Valve* raw_red_valve_ptr = new Gameplay::Valve(
        Math::Vector2D { 110.0f, 318.0f }, 
        std::move(red_valve_material),
        0.7f,  // scale
        true,  // state (enabled)
        0.0f,  // start rotation angle
        120.0f // start velocity of rotation
    );
    main_scene.addObject(std::unique_ptr<Core::GameObject>(raw_red_valve_ptr));

    Graphic::Texture blue_valve_tex("assets/textures/blue_valve.png");
    Graphic::SpriteMaterial blue_valve_material(std::move(blue_valve_tex));
    
    Gameplay::Valve* raw_blue_valve_ptr = new Gameplay::Valve(
        Math::Vector2D { 525.0f, 318.0f }, 
        std::move(blue_valve_material),
        0.7f,  // scale
        true,  // state (enabled)
        0.0f,  // start rotation angle
        120.0f // start velocity of rotation
    );
    main_scene.addObject(std::unique_ptr<Core::GameObject>(raw_blue_valve_ptr));
    
    Gameplay::MolecularContainer* raw_vessel_ptr = new Gameplay::MolecularContainer(
        Math::Vector2D { 190.0f, 115.0f }, 
        Math::Vector2D { 305.0f, 260.0f }
    );
    
    // raw_vessel_ptr->setValveLink(raw_valve_ptr);
    
    Gameplay::MoleculeSpawner left_pipe {};
    left_pipe.pos            = Math::Vector2D { 200.0f, 205.0f }; 
    left_pipe.base_velocity  = Math::Vector2D { 130.0f, 0.0f };
    left_pipe.type_to_spawn  = Gameplay::SpawnType::Circle;
    left_pipe.spawn_interval = 0.4f;
    raw_vessel_ptr->addSpawner(left_pipe);

    Gameplay::MoleculeSpawner right_pipe;
    right_pipe.pos            = Math::Vector2D { 480.0f, 205.0f }; 
    right_pipe.base_velocity  = Math::Vector2D { -130.0f, 0.0f };
    right_pipe.type_to_spawn  = Gameplay::SpawnType::Square;
    right_pipe.spawn_interval = 0.4f;
    raw_vessel_ptr->addSpawner(right_pipe);

    main_scene.addObject(std::unique_ptr<Core::GameObject>(raw_vessel_ptr));

    while (!Graphic::Adapter::shouldClose()) {
        float dt = Graphic::Adapter::getFrameTime(); 

        auto& spawners = raw_vessel_ptr->spawners();
           
        spawners[0].enabled_ = raw_red_valve_ptr->isOpen();
           
        spawners[1].enabled_ = raw_blue_valve_ptr->isOpen();
           
        main_scene.update(dt); 

        Graphic::Adapter::beginDrawing();
            Graphic::Adapter::clearBackground(Graphic::Colors::Black);
            
            main_scene.bind(main_camera);        
                main_scene.draw();
            main_scene.unbind(main_camera);
        
        Graphic::Adapter::endDrawing();
    }
  
    Graphic::Adapter::closeWindow();
    return 0;
}