#include <cmath>
#include <algorithm>
#include "Core/ChemicalEngine.hpp"
#include "Gameplay/CircleMolecule.hpp"
#include "Gameplay/SquareMolecule.hpp"

namespace Core {

static bool checkIntersection (const Core::GameObject& obj1, const Core::GameObject& obj2) {
    auto type1 = obj1.getHitboxType();
    auto type2 = obj2.getHitboxType();

    if (obj1.getObjectType() == Core::ObjectType::Heater || obj2.getObjectType() == Core::ObjectType::Heater) return false;

    if (type1 == HitboxType::Circle && type2 == HitboxType::Circle) {
        float dist_sq = (obj2.pos().x() - obj1.pos().x()) * (obj2.pos().x() - obj1.pos().x()) +
                        (obj2.pos().y() - obj1.pos().y()) * (obj2.pos().y() - obj1.pos().y());
        float min_dist = obj1.radius() + obj2.radius();
        return dist_sq < (min_dist * min_dist);
    }
    else if (type1 == HitboxType::Rectangle && type2 == HitboxType::Rectangle) {
        return (obj1.pos().x() < obj2.pos().x() + obj2.size().x() &&
                obj1.pos().x() + obj1.size().x() > obj2.pos().x() &&
                obj1.pos().y() < obj2.pos().y() + obj2.size().y() &&
                obj1.pos().y() + obj1.size().y() > obj2.pos().y());
    }

    const Core::GameObject& square = (type1 == HitboxType::Rectangle) ? obj1 : obj2;
    const Core::GameObject& circle = (type1 == HitboxType::Circle) ? obj1 : obj2;
    
    float closest_x = std::clamp(circle.pos().x(), square.pos().x(), square.pos().x() + square.size().x());
    float closest_y = std::clamp(circle.pos().y(), square.pos().y(), square.pos().y() + square.size().y());
    
    float dist_sq = (circle.pos().x() - closest_x) * (circle.pos().x() - closest_x) +
                    (circle.pos().y() - closest_y) * (circle.pos().y() - closest_y);
    return dist_sq < (circle.radius() * circle.radius());
}
    
// -------------------------------------------------------------------------------
// --- Implementation Of Static Methods ---

void (*resolveReaction[4]) (Core::GameObject& obj1, Core::GameObject& obj2,
                            std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue) = {
    ChemicalEngine::reactCircleCircle,
    ChemicalEngine::reactCircleSquare,
    ChemicalEngine::reactSquareCircle,
    ChemicalEngine::reactSquareSquare
};

void ChemicalEngine::reactCircleCircle(Core::GameObject& circle1, Core::GameObject& circle2, 
                                      std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue) {
    Math::Vector2D new_vel = (circle1.velocity() * circle1.mass() + circle2.velocity() * circle2.mass()) * (1.0f / (circle1.mass() + circle2.mass()));
    Math::Vector2D spawn_pos = (circle1.pos() + circle2.pos()) * 0.5f;

    circle1.setEnabled(false);
    circle2.setEnabled(false);

    spawn_queue.push_back(std::make_unique<Gameplay::SquareMolecule>(
        spawn_pos, new_vel, Math::Vector2D{ circle1.radius() * 4.0f, circle1.radius() * 4.0f }, Graphic::Colors::Blue, 2.0f
    ));
}

void ChemicalEngine::reactCircleSquare(Core::GameObject& circle, Core::GameObject& square, 
                                      std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue) {
    float new_mass = circle.mass() + square.mass();
    Math::Vector2D new_vel = (circle.velocity() * circle.mass() + square.velocity() * square.mass()) * (1.0f / new_mass);

    circle.setEnabled(false);
    square.setEnabled(false);

    Math::Vector2D new_size = { square.size().x() + circle.radius() * 2.0f, square.size().y() + circle.radius() * 2.0f };

    spawn_queue.push_back(std::make_unique<Gameplay::SquareMolecule>(
        square.pos(), new_vel, new_size, Graphic::Colors::Green, new_mass
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

void ChemicalEngine::reactSquareSquare(Core::GameObject& square1, Core::GameObject& square2, 
                                      std::vector<std::unique_ptr<Core::GameObject>>& spawn_queue) {
    if (square1.getObjectType() == Core::ObjectType::Heater || square2.getObjectType() == Core::ObjectType::Heater) return;
    if (square1.mass() <= 0.0f || square2.mass() <= 0.0f) return;

    int count_to_spawn = static_cast<int>(square1.mass() + square2.mass());
    if (count_to_spawn <= 0) return;

    Math::Vector2D base_pos = (square1.pos() + square2.pos()) * 0.5f;

    square1.setEnabled(false);
    square2.setEnabled(false);

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
    std::vector<std::unique_ptr<Core::GameObject>> spawn_queue {};

    for (size_t i = 0; i < objects.size(); ++i) {
        GameObject* obj1 = objects[i].get();
        if (!obj1 || !obj1->isEnabled()) continue;
        
        for (size_t j = i + 1; j < objects.size(); ++j) {

            GameObject* obj2 = objects[j].get();
            if (!obj2 || !obj2->isEnabled()) continue;

            if (checkIntersection(*obj1, *obj2)) {
                
                auto type1 = obj1->getHitboxType();
                auto type2 = obj2->getHitboxType();

                resolveReaction[static_cast<int>(type1) * 2 + static_cast<int>(type2)](*obj1, *obj2, spawn_queue);
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