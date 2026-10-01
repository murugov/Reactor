#include <cstdlib>
#include "Core/PhysicsEngine.hpp"
#include "Gameplay/CircleMolecule.hpp"
#include "Gameplay/MolecularContainer.hpp"
#include "Gameplay/SquareMolecule.hpp"

namespace Gameplay {

void MolecularContainer::addMolecule(std::unique_ptr<Core::GameObject> mol) {
    if (mol) {
        sub_objects_.push_back(std::move(mol));         // NOTE: There is some overhead involved here, but on the plus side, it scales better.
    }
}

void MolecularContainer::addSpawner(const MoleculeSpawner& spawner) {
        spawners_.push_back(spawner);
}
    
void MolecularContainer::update(float dt) {
    if (!enabled_) return;

    for (auto& spawner : spawners_) {
        if (spawner.enabled_) {
            spawner.timer += dt;
            if (spawner.timer >= spawner.spawn_interval) {
                spawner.timer = 0.0f;
                Math::Vector2D rand_vel{ 
                    spawner.base_velocity.x() - (rand() % 60), 
                    spawner.base_velocity.y() + (rand() % 60) 
                };
    
                if (spawner.type_to_spawn == SpawnType::Circle) {
                    addMolecule(std::make_unique<CircleMolecule>(spawner.pos, rand_vel, 3.0f, Graphic::Colors::Red));
                } else if (spawner.type_to_spawn == SpawnType::Square) {
                    addMolecule(std::make_unique<SquareMolecule>(spawner.pos, rand_vel, Math::Vector2D { 6.0f, 6.0f }, Graphic::Colors::Blue));
                }
            }
        }
    }

    for (auto& obj : sub_objects_) {
        if (obj && obj->isEnabled()) {
            obj->update(dt);
        }
    }

    Core::PhysicsEngine::collideObjects(sub_objects_);
    Core::PhysicsEngine::collideWithWalls(sub_objects_, x_min_, x_max_, y_min_, y_max_);
}

void MolecularContainer::draw() const {
    if (!enabled_) return;

    for (const auto& obj : sub_objects_) {
        if (obj && obj->isEnabled()) {
            obj->draw();
        }
    }
}

} // namespace Gameplay
