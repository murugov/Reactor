// Gameplay/MolecularContainer.hpp
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
};
    
class MolecularContainer : public Core::GameObject {
private:
    std::vector<std::unique_ptr<Core::GameObject>> sub_objects_ {};
    float x_min_, x_max_, y_min_, y_max_;
    std::vector<MoleculeSpawner> spawners_ {};

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
    // --- Methods Prototypes ---
    
    void addMolecule (std::unique_ptr<Core::GameObject> mol);
    void addSpawner  (const MoleculeSpawner& spawner);
    
    // --- Virtual Methods Prototypes ---
    
    void update (float dt) override;
    void draw   () const override;

    Core::HitboxType getHitboxType () const override { return Core::HitboxType::None; }
};

} // namespace Gameplay

#endif