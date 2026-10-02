#include "Core/ChemicalEngine.hpp"
#include "Core/GameObject.hpp"
#include "Core/PhysicsEngine.hpp"
#include "Gameplay/CircleMolecule.hpp"
#include "Gameplay/MolecularContainer.hpp"
#include "Gameplay/SquareMolecule.hpp"

namespace Gameplay {

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---
    
void MolecularContainer::addMolecule(std::unique_ptr<Core::GameObject> mol) {
    if (mol) {
        sub_objects_.push_back(std::move(mol));
    }
}
    
void MolecularContainer::addSpawner(const MoleculeSpawner& spawner) {
    spawners_.push_back(spawner);
}

// -------------------------------------------------------------------------------
// --- Implementation Of Virtual Methods ---

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
                    addMolecule(std::make_unique<CircleMolecule>(spawner.pos, rand_vel, 1.0f, Graphic::Colors::Red));
                } else if (spawner.type_to_spawn == SpawnType::Square) {
                    addMolecule(std::make_unique<SquareMolecule>(spawner.pos, rand_vel, Math::Vector2D { 4.0f, 4.0f }, Graphic::Colors::Blue));
                }
            }
        }
    }

    // --- Position updates and temperature data collection ---
    float total_kinetic_energy = 0.0f;
    int molecule_count = 0;

    for (auto& obj : sub_objects_) {
        if (obj && obj->isEnabled()) {
            obj->update(dt);

            if (obj->getObjectType() != Core::ObjectType::Heater) {
                Math::Vector2D vel = obj->velocity();
                float speed_sq = vel.x() * vel.x() + vel.y() * vel.y();
                
                // E_k = 0.5 * m * v^2
                total_kinetic_energy += 0.5f * obj->mass() * speed_sq;
                molecule_count++;
            }
        }
    }

    // --- Calculating average temperature (scaled for display) ---
    if (molecule_count > 0) {
        current_temperature_ = (total_kinetic_energy / static_cast<float>(molecule_count)) * 0.1f;
    } else {
        current_temperature_ = 0.0f;
    }
    
    // --- Processing reactions and collisions ---
    Core::ChemicalEngine::processReactions(sub_objects_);
    Core::PhysicsEngine::collideObjects(sub_objects_);

    // --- Interacting with heater ---
    if (heater_ptr_ && heater_ptr_->isEnabled()) {
        for (auto& mol : sub_objects_) {
            if (!mol || !mol->isEnabled()) continue;

            if (mol->getHitboxType() == Core::HitboxType::Circle) {
                Core::PhysicsEngine::resolveSquareCircle(*heater_ptr_, *mol);
            } 
            else if (mol->getHitboxType() == Core::HitboxType::Rectangle) {
                Core::PhysicsEngine::resolveSquareSquare(*heater_ptr_, *mol);
            }
        }
    }
    
    // --- Collision with walls and pressure calculation ---
    Core::PhysicsEngine::collideWithWalls(sub_objects_, x_min_, x_max_, y_min_, y_max_);

    float width = x_max_ - x_min_;
    float height = y_max_ - y_min_;
    float container_area = width * height;

    if (container_area > 0.0f && molecule_count > 0) {
        float concentration = static_cast<float>(molecule_count) / container_area; // n = N / V
        
        const float k_boltzmann = 400.0f; 

        // P = n * k * T
        current_pressure_ = concentration * k_boltzmann * current_temperature_;
    } else {
        current_pressure_ = 0.0f;
    }
    
    accumulated_impulse_ = 0.0f;
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