#include "Adapter.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Vector.hpp"
#include "Scene.hpp"

// TODO: (MolecularManager == controler) = true

// NOTE: Obviously hardcoded main for test
int main() {
  const int window_width  = 800;
  const int window_height = 450;

  Graphic::Adapter::initWindow(window_width, window_height, "Reactor");

  Graphic::Texture main_bg("assets/textures/reactor.png");
  Graphic::Canvas main_screen(Math::Vector2D { 0.0f, 0.0f }, 800, 450, Graphic::Colors::White, main_bg);
  Graphic::Camera main_camera(Math::Vector2D { 0.0f, 0.0f }, Math::Vector2D { 400.0f, 300.0f }, 1.0f);
  Graphic::Scene main_scene(main_screen);

  Graphic::Texture red_valve_bg("assets/textures/red_valve.png");
  Graphic::Canvas red_valve_screen(Math::Vector2D { 118.0f, 322.0f }, 60, 60, Graphic::Colors::White, red_valve_bg);
  Graphic::Camera red_valve_camera(Math::Vector2D { 118.0f + 30.0f, 322.0f + 30.0f }, Math::Vector2D { 118.0f + 30.0f, 322.0f + 30.0f });
  Graphic::Scene red_valve_scene(red_valve_screen);

  int angle = 0;
  
  while (!Graphic::Adapter::shouldClose()) {
      Graphic::Adapter::beginDrawing();
        main_screen.draw();
        red_valve_camera.begin();
            red_valve_camera.set_rotation(static_cast<float>(angle % 360));
            red_valve_screen.draw();
        red_valve_camera.end();
        
      Graphic::Adapter::endDrawing();
      angle++;
  }
  
  Graphic::Adapter::closeWindow();
}