#include <cstdio>
#include "Core/Scene.hpp"
#include "Gameplay/Heater.hpp"
#include "Gameplay/MolecularContainer.hpp"
<<<<<<< HEAD
#include "Gameplay/Plot.hpp"
#include "Gameplay/TemperatureController.hpp"
=======
>>>>>>> 1c2f76a8d19988a9f911ee2d12fce7bfbec2c368
#include "Gameplay/Valve.hpp"
#include "Graphic/Adapter.hpp"
#include "Graphic/Canvas.hpp"
#include "Graphic/Camera.hpp"
<<<<<<< HEAD
#include "Graphic/Colors.hpp"
=======
>>>>>>> 1c2f76a8d19988a9f911ee2d12fce7bfbec2c368
#include "Graphic/SpriteMaterial.hpp"
#include "Graphic/Texture.hpp"
#include "Math/Vector.hpp"

int main() {
    const int window_width  = 800;
    const int window_height = 450;

    // -------------------------------------------------------------------------------
    // --- Initialize Window ---
    
    Graphic::Adapter::initWindow(window_width, window_height, "Reactor");
    
    Graphic::Camera main_camera(Math::Vector2D { 0.0f, 0.0f }, Math::Vector2D { 0.0f, 0.0f }, 1.0f);
    Core::Scene main_scene({ 0.0f, 0.0f }, window_width, window_height, "assets/textures/reactor.png");

    // -------------------------------------------------------------------------------
    // --- Initialize Objects ---

    // --- Red Valve ---
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

    // --- Blue Valve ---
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

    // --- Molecular Container ---
    
    Gameplay::MolecularContainer* raw_vessel_ptr = new Gameplay::MolecularContainer(
        Math::Vector2D { 190.0f, 115.0f }, 
        Math::Vector2D { 305.0f, 260.0f }
    );

    // --- Molecule Spawners ---
    
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

    // --- Temperature Controller ---
    
    Graphic::Texture temperature_controller_tex("assets/textures/temperature_controller.png");
    Graphic::SpriteMaterial temperature_controller_material(std::move(temperature_controller_tex));
    
    Gameplay::TemperatureController* raw_temperature_controller_ptr = new Gameplay::TemperatureController(
        Math::Vector2D { 85.0f, 100.0f }, 
        std::move(temperature_controller_material),
        Math::Vector2D { 75.0f, 75.0f },
        true,  // state (enabled)
        0.0f   // start rotation angle
    );
    main_scene.addObject(std::unique_ptr<Core::GameObject>(raw_temperature_controller_ptr));
    
    // --- Heater ---
    
    Graphic::Texture heater_tex("assets/textures/heater.png");
    Graphic::SpriteMaterial heater_material(std::move(heater_tex));
    
    Gameplay::Heater* raw_heater_ptr = new Gameplay::Heater(
        Math::Vector2D { 190.0f, 370.0f },
        std::move(heater_material),
        Math::Vector2D { 315.0f, 35.0f }
    );
    main_scene.addObject(std::unique_ptr<Core::GameObject>(raw_heater_ptr));

    raw_heater_ptr->setTemperatureController(raw_temperature_controller_ptr);

    raw_vessel_ptr->setHeater(raw_heater_ptr);

    // --- Plots ---
    
    Graphic::Canvas temp_canvas({ 600.0f, 195.0f }, { 165.0f, 75.0f }, Graphic::Colors::White);
    Graphic::Canvas press_canvas({ 600.0f, 280.0f }, { 165.0f, 75.0f }, Graphic::Colors::White);

    Gameplay::Plot temp_plot(temp_canvas, 150, Graphic::Colors::Red);
    Gameplay::Plot press_plot(press_canvas, 150, Graphic::Colors::Blue);
     
    // -------------------------------------------------------------------------------
    // --- Main Loop ---

    bool reactor_melted_down = false;
    
    while (!Graphic::Adapter::shouldClose()) {
        int current_fps = Graphic::Adapter::getFPS();

        float dt = Graphic::Adapter::getFrameTime(); 

        if (current_fps < 20 && current_fps > 0) {
            reactor_melted_down = true;
            raw_vessel_ptr->setEnabled(false);
        }

        if (!reactor_melted_down) {
            auto& spawners = raw_vessel_ptr->spawners();
               
            spawners[0].enabled_ = raw_red_valve_ptr->isOpen();
            spawners[1].enabled_ = raw_blue_valve_ptr->isOpen();
               
            main_scene.update(dt);
           
            temp_plot.pushValue(raw_vessel_ptr->temperature());
            press_plot.pushValue(raw_vessel_ptr->pressure()); 
        }
    while (!Graphic::Adapter::shouldClose()) {
        float dt = Graphic::Adapter::getFrameTime(); 

        auto& spawners = raw_vessel_ptr->spawners();
           
        spawners[0].enabled_ = raw_red_valve_ptr->isOpen();
           
        spawners[1].enabled_ = raw_blue_valve_ptr->isOpen();
           
        main_scene.update(dt); 

        Graphic::Adapter::beginDrawing();
            Graphic::Adapter::clearBackground(Graphic::Colors::Black);
            
            if (!reactor_melted_down) {
                main_scene.bind(main_camera);        
                    main_scene.draw();
                main_scene.unbind(main_camera);

                char temp_buffer[32]  = {};
                char press_buffer[32] = {};

                std::snprintf(temp_buffer, sizeof(temp_buffer), "TEMP: %.1f C", raw_vessel_ptr->temperature());
                std::snprintf(press_buffer, sizeof(press_buffer), "PRES: %.1f kPa", raw_vessel_ptr->pressure());

                Graphic::Adapter::drawText(temp_buffer, 600, 20, 20, Graphic::Colors::White);
                Graphic::Adapter::drawText(press_buffer, 600, 50, 20, Graphic::Colors::White);

                temp_plot.draw();
                press_plot.draw();
            } 
            else {
                Graphic::Adapter::clearBackground(Graphic::Colors::DarkGray); 
                
                Graphic::Adapter::drawText("SYSTEM FAILURE: DUMBASS DETECTED", 40, 180, 36, Graphic::Colors::Red);
                Graphic::Adapter::drawText("REACTOR TERMINATED DUE TO FPS MELTDOWN", 150, 240, 20, Graphic::Colors::White);
            }
            main_scene.bind(main_camera);        
                main_scene.draw();
            main_scene.unbind(main_camera);
        
        Graphic::Adapter::endDrawing();
    }
  
    Graphic::Adapter::closeWindow();
    return 0;
}
