#include <cmath>
#include <algorithm>
#include "Core/ChemicalEngine.hpp"
#include "Gameplay/CircleMolecule.hpp"
#include "Gameplay/SquareMolecule.hpp"

namespace Core {

// -------------------------------------------------------------------------------
// --- Implementation Of Static Methods ---
    
bool ChemicalEngine::checkIntersection(const Core::GameObject& obj1, const Core::GameObject& obj2) {
    auto t1 = obj1.getHitboxType();
    auto t2 = obj2.getHitboxType();
    
    if (t1 == HitboxType::Circle && t2 == HitboxType::Circle) {
        float dist_sq = (obj2.pos().x() - obj1.pos().x()) * (obj2.pos().x() - obj1.pos().x()) +
                        (obj2.pos().y() - obj1.pos().y()) * (obj2.pos().y() - obj1.pos().y());
        float min_dist = obj1.radius() + obj2.radius();
        return dist_sq < (min_dist * min_dist);
    }
    else if (t1 == HitboxType::Rectangle && t2 == HitboxType::Rectangle) {
        return (obj1.pos().x() < obj2.pos().x() + obj2.size().x() &&
                obj1.pos().x() + obj1.size().x() > obj2.pos().x() &&
                obj1.pos().y() < obj2.pos().y() + obj2.size().y() &&
                obj1.pos().y() + obj1.size().y() > obj2.pos().y());
    }

    const Core::GameObject& square = (t1 == HitboxType::Rectangle) ? obj1 : obj2;
    const Core::GameObject& circle = (t1 == HitboxType::Circle) ? obj1 : obj2;
    
    float closest_x = std::clamp(circle.pos().x(), square.pos().x(), square.pos().x() + square.size().x());
    float closest_y = std::clamp(circle.pos().y(), square.pos().y(), square.pos().y() + square.size().y());
    
    float dist_sq = (circle.pos().x() - closest_x) * (circle.pos().x() - closest_x) +
                    (circle.pos().y() - closest_y) * (circle.pos().y() - closest_y);
    return dist_sq < (circle.radius() * circle.radius());
}

void ChemicalEngine::reactCircleCircle(Core::GameObject& c1, Core::GameObject& c2, 
                                      std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue) {
    Math::Vector2D new_vel = (c1.velocity() * c1.mass() + c2.velocity() * c2.mass()) * (1.0f / (c1.mass() + c2.mass()));
    Math::Vector2D spawn_pos = (c1.pos() + c2.pos()) * 0.5f;

    c1.setEnabled(false);
    c2.setEnabled(false);

    spawn_queue.push_back(std::make_unique<Gameplay::SquareMolecule>(
        spawn_pos, new_vel, Math::Vector2D{ c1.radius() * 4.0f, c1.radius() * 4.0f }, Graphic::Colors::Blue, 2.0f
    ));
}

void ChemicalEngine::reactSquareCircle(Core::GameObject& square, Core::GameObject& circle, 
                                      std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue) {
    float new_mass = square.mass() + circle.mass();
    Math::Vector2D new_vel = (square.velocity() * square.mass() + circle.velocity() * circle.mass()) * (1.0f / new_mass);

    square.setEnabled(false);
    circle.setEnabled(false);

    Math::Vector2D new_size = { square.size().x() + circle.radius() * 2.0f, square.size().y() + circle.radius() * 2.0f };

    spawn_queue.push_back(std::make_unique<Gameplay::SquareMolecule>(
        square.pos(), new_vel, new_size, Graphic::Colors::Green, new_mass
    ));
}

void ChemicalEngine::reactSquareSquare(Core::GameObject& s1, Core::GameObject& s2, 
                                      std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue) {
    if (s1.getObjectType() == Core::ObjectType::Heater || s2.getObjectType() == Core::ObjectType::Heater) return;
    if (s1.mass() <= 0.0f || s2.mass() <= 0.0f) return;

    int count_to_spawn = static_cast<int>(s1.mass() + s2.mass());
    if (count_to_spawn <= 0) return;

    Math::Vector2D base_pos = (s1.pos() + s2.pos()) * 0.5f;

    s1.setEnabled(false);
    s2.setEnabled(false);

    const float molecule_radius = 1.0f;
    const float spread_distance = molecule_radius * 5.0f; 

    for (int i = 0; i < count_to_spawn; ++i) {
        float angle = (360.0f / static_cast<float>(count_to_spawn)) * static_cast<float>(i) * (3.14159265f / 180.0f);
        
        float cos_val = std::cos(angle);
        float sin_val = std::sin(angle);
        
        Math::Vector2D explode_vel { cos_val * 160.0f, sin_val * 160.0f };

        Math::Vector2D shifted_pos {
            base_pos.x() + cos_val * spread_distance,
            base_pos.y() + sin_val * spread_distance
        };

        spawn_queue.push_back(std::make_unique<Gameplay::CircleMolecule>(
            shifted_pos, explode_vel, molecule_radius, Graphic::Colors::Red, 1.0f
        ));
    }
}

void ChemicalEngine::processReactions(std::vector<std::unique_ptr<Core::GameObject>>& objects) {
    std::vector<std::unique_ptr<Core::GameObject>> spawn_queue;

    for (size_t i = 0; i < objects.size(); ++i) {
        if (!objects[i] || !objects[i]->isEnabled()) continue;
        
        if (objects[i]->getObjectType() == Core::ObjectType::Heater) continue;

        for (size_t j = i + 1; j < objects.size(); ++j) {
            if (!objects[j] || !objects[j]->isEnabled()) continue;
            if (objects[j]->getObjectType() == Core::ObjectType::Heater) continue;

            if (checkIntersection(*objects[i], *objects[j])) {
                auto t1 = objects[i]->getHitboxType();
                auto t2 = objects[j]->getHitboxType();

                if (t1 == HitboxType::Circle && t2 == HitboxType::Circle) {
                    reactCircleCircle(*objects[i], *objects[j], spawn_queue);
                    break;
                }
                else if (t1 == HitboxType::Rectangle && t2 == HitboxType::Rectangle) {
                    reactSquareSquare(*objects[i], *objects[j], spawn_queue);
                    break;
                }
                else if (t1 == HitboxType::Rectangle && t2 == HitboxType::Circle) {
                    reactSquareCircle(*objects[i], *objects[j], spawn_queue);
                    break;
                }
                else if (t1 == HitboxType::Circle && t2 == HitboxType::Rectangle) {
                    reactSquareCircle(*objects[j], *objects[i], spawn_queue);
                    break;
                }
            }
        }
    }

    objects.erase(
        std::remove_if(objects.begin(), objects.end(), 
            [](const std::unique_ptr<Core::GameObject>& obj) { return !obj || !obj->isEnabled(); }),
        objects.end()
    );

    for (auto& new_mol : spawn_queue) {
        objects.push_back(std::move(new_mol));
    }
}

} // namespace Core