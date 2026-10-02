#ifndef MOLECULAR_CONTAINER_HPP
#define MOLECULAR_CONTAINER_HPP

#include <vector>
#include <memory>
#include "Core/GameObject.hpp"

namespace Gameplay {

enum class SpawnType {
    Circle,
    Square
};

struct MoleculeSpawner {
    Math::Vector2D pos;
    Math::Vector2D base_velocity;
    SpawnType type_to_spawn;
    float spawn_interval = 0.4f;
    float timer = 0.0f;
    bool enabled_ = false;
};
    
class MolecularContainer : public Core::GameObject {
private:
    std::vector<std::unique_ptr<Core::GameObject>> sub_objects_ {};
    float x_min_, x_max_, y_min_, y_max_;
    std::vector<MoleculeSpawner> spawners_ {};
    Core::GameObject* heater_ptr_ = nullptr;

    float current_temperature_ = 0.0f;
    float current_pressure_    = 0.0f;
    float accumulated_impulse_ = 0.0f;
    
public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---
    
    MolecularContainer (Math::Vector2D pos, Math::Vector2D size)
        : Core::GameObject (pos)
        , x_min_(pos.x())
        , x_max_(pos.x() + size.x())
        , y_min_(pos.y())
        , y_max_(pos.y() + size.y()) 
    {}

    // --- Destructor ---
    
    ~MolecularContainer () override = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    std::vector<MoleculeSpawner>& spawners() { return spawners_; }
    
    float temperature() const { return current_temperature_; }
    float pressure()    const { return current_pressure_; }    

    // -------------------------------------------------------------------------------
    // --- Setters ---

    void setHeater (Core::GameObject* heater) { heater_ptr_ = heater; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void addMolecule (std::unique_ptr<Core::GameObject> mol);
    void addSpawner  (const MoleculeSpawner& spawner);

    void registerWallImpact(float impulse) { accumulated_impulse_ += impulse; }

    // --- Virtual Methods Prototypes ---
    
    void update (float dt) override;
    void draw   () const override;

    Core::ObjectType getObjectType () const override { return Core::ObjectType::Unknown; }
    Core::HitboxType getHitboxType () const override { return Core::HitboxType::None; }
};

} // namespace Gameplay

#endif