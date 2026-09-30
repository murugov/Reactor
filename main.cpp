#include "Core/Scene.hpp"
#include "Gameplay/MolecularContainer.hpp"
#include "Graphic/Adapter.hpp"
#include "Graphic/Camera.hpp"
#include "Math/Vector.hpp"

int main() {
    const int window_width  = 800;
    const int window_height = 450;

    Graphic::Adapter::initWindow(window_width, window_height, "Reactor");
    
    Graphic::Camera main_camera(Math::Vector2D { 0.0f, 0.0f }, Math::Vector2D { 0.0f, 0.0f }, 1.0f);
    Core::Scene main_scene({ 0.0f, 0.0f }, window_width, window_height, "assets/textures/reactor.png");

    Gameplay::MolecularContainer* raw_vessel_ptr = new Gameplay::MolecularContainer(
        Math::Vector2D { 190.0f, 115.0f }, 
        Math::Vector2D { 305.0f, 260.0f }
    );
    
    Gameplay::MoleculeSpawner left_pipe {};
    left_pipe.pos            = Math::Vector2D { 10.0f, 205.0f };
    left_pipe.base_velocity  = Math::Vector2D { 130.0f, 0.0f };
    left_pipe.type_to_spawn  = Gameplay::SpawnType::Circle;
    left_pipe.spawn_interval = 0.4f;
    raw_vessel_ptr->addSpawner(left_pipe);

    Gameplay::MoleculeSpawner right_pipe;
    right_pipe.pos            = Math::Vector2D { 495.0f, 205.0f };
    right_pipe.base_velocity  = Math::Vector2D { -130.0f, 0.0f };
    right_pipe.type_to_spawn  = Gameplay::SpawnType::Square;
    right_pipe.spawn_interval = 0.4f;
    raw_vessel_ptr->addSpawner(right_pipe);
    
    main_scene.addObject(std::unique_ptr<Core::GameObject>(raw_vessel_ptr));

    while (!Graphic::Adapter::shouldClose()) {
        float dt = Graphic::Adapter::getFrameTime(); 
     
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