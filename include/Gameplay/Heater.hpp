#ifndef HEATER_HPP
#define HEATER_HPP

#include "Core/GameObject.hpp"
#include "Graphic/SpriteMaterial.hpp"
#include "Math/Vector.hpp"

namespace Gameplay {

class Heater : public Core::GameObject {
private:
    Graphic::SpriteMaterial material_;
    Math::Vector2D size_;
    Core::GameObject* temperature_controller_ptr_ = nullptr;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    Heater(Math::Vector2D pos,
        Graphic::SpriteMaterial&& material,
        Math::Vector2D size,
        bool state = true,
        Math::Vector2D vel = { 0.0f, 0.0f })
        : Core::GameObject(pos, vel, -1.0f, state)
        , material_(std::move(material))
        , size_(size)
        {}

    // --- Destructor ---
    
    ~Heater() override = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    Math::Vector2D size() const override { return Math::Vector2D{ size_.x(), size_.y() }; }
    
    Core::GameObject* getTemperatureController() const { return temperature_controller_ptr_; }

    // -------------------------------------------------------------------------------
    // --- Setters ---

    void setTemperatureController(Core::GameObject* ptr) { temperature_controller_ptr_ = ptr; }

    // -------------------------------------------------------------------------------
    // --- Virtual Methods Prototypes ---
    
    void update(float /*dt*/) override {}
    void draw() const override;

    Core::ObjectType getObjectType() const override { return Core::ObjectType::Heater; }
    Core::HitboxType getHitboxType() const override { return Core::HitboxType::Rectangle; }
};

} // namespace Gameplay

#endif