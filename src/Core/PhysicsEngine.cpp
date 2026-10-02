#include <cmath>
#include <algorithm>
#include "Core/GameObject.hpp"
#include "Gameplay/Heater.hpp"
#include "Gameplay/SquareMolecule.hpp"
#include "Core/PhysicsEngine.hpp"

namespace Core {

static void applyImpulse (Core::GameObject& obj1, Core::GameObject& obj2, const Math::Vector2D& normal) {
    Math::Vector2D vel1 = obj1.velocity();
    Math::Vector2D vel2 = obj2.velocity();
    
    Math::Vector2D rel_vel = vel1 - vel2;
    float speed_on_normal = rel_vel.x() * normal.x() + rel_vel.y() * normal.y();

    if (speed_on_normal > 0.0f) {
        float impulse = (2.0f * speed_on_normal) / (obj1.mass() + obj2.mass());
        
        obj1.setVelocity(vel1 - normal * (impulse * obj2.mass()));
        obj2.setVelocity(vel2 + normal * (impulse * obj1.mass()));
    }
}

static void handleHeaterEffects (Core::GameObject& obj1, Core::GameObject& obj2) {
    if (obj1.getObjectType() == Core::ObjectType::Heater) {
        auto* heater = static_cast<Gameplay::Heater*>(&obj1);
        auto* temperature_controller = heater->getTemperatureController();
        if (temperature_controller) {
            obj2.setVelocity(obj2.velocity() * (temperature_controller->rotation_angle() / 18.0f + 1.0f) );
        }
    }
    else if (obj2.getObjectType() == Core::ObjectType::Heater) {
        auto* heater = static_cast<Gameplay::Heater*>(&obj2);
        auto* temperature_controller = heater->getTemperatureController();
        if (temperature_controller) {
            obj1.setVelocity(obj1.velocity() * (temperature_controller->rotation_angle() / 18.0f + 1.0f));

        }
    }
}

// -------------------------------------------------------------------------------
// --- Implementation Of Static Methods ---

static void (*resolveCollision[4]) (Core::GameObject& obj1, Core::GameObject& obj2) = {
    PhysicsEngine::resolveCircleCircle,
    PhysicsEngine::resolveCircleSquare,
    PhysicsEngine::resolveSquareCircle,
    PhysicsEngine::resolveSquareSquare
};

void PhysicsEngine::collideObjects (std::vector<std::unique_ptr<GameObject>>& objects) {
    for (size_t i = 0; i < objects.size(); ++i) {
        GameObject* obj1 = objects[i].get();
        if (!obj1 || !obj1->isEnabled()) continue;

        for (size_t j = i + 1; j < objects.size(); ++j) {
            GameObject* obj2 = objects[j].get();
            if (!obj2 || !obj2->isEnabled()) continue;

            auto type1 = obj1->getHitboxType();
            auto type2 = obj2->getHitboxType();

            resolveCollision[static_cast<int>(type1) * 2 + static_cast<int>(type2)](*obj1, *obj2);
        }
    }
}

void PhysicsEngine::resolveCircleCircle (Core::GameObject& circle1, Core::GameObject& circle2) {
    Math::Vector2D pos1 = circle1.pos();
    Math::Vector2D pos2 = circle2.pos();
    float r1 = circle1.radius();
    float r2 = circle2.radius();

    Math::Vector2D delta = pos2 - pos1;
    float distance = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());
    float min_dist = r1 + r2;

    if (distance < min_dist && distance > 0.0f) {
        float overlap = min_dist - distance;
        Math::Vector2D normal = delta * (1.0f / distance);
        
        circle1.setPosition(pos1 - normal * (overlap * 0.5f));
        circle2.setPosition(pos2 + normal * (overlap * 0.5f));

        applyImpulse(circle1, circle2, normal);
        handleHeaterEffects(circle1, circle2);
    }
}

void PhysicsEngine::resolveCircleSquare (Core::GameObject& circle, Core::GameObject& square) {
    Math::Vector2D r_pos = circle.pos();
    Math::Vector2D r_size = circle.size();
    Math::Vector2D c_pos = square.pos();
    float radius = square.radius();

    float closest_x = std::clamp(c_pos.x(), r_pos.x(), r_pos.x() + r_size.x());
    float closest_y = std::clamp(c_pos.y(), r_pos.y(), r_pos.y() + r_size.y());

    float distance_x = c_pos.x() - closest_x;
    float distance_y = c_pos.y() - closest_y;
    float distance = std::sqrt(distance_x * distance_x + distance_y * distance_y);

    if (distance < radius) {
        Math::Vector2D normal {0.0f, 0.0f};
        float overlap = 0.0f;

        if (std::abs(distance) < 1e-5f) {
            float center_x = r_pos.x() + r_size.x() * 0.5f;
            normal = (c_pos.x() > center_x) ? Math::Vector2D { 1.0f, 0.0f } : Math::Vector2D{ -1.0f, 0.0f };
            overlap = radius;
        } else {
            normal = { distance_x / distance, distance_y / distance };
            overlap = radius - distance;
        }

        circle.setPosition(r_pos - normal * (overlap * 0.5f));
        square.setPosition(c_pos + normal * (overlap * 0.5f));

        applyImpulse(circle, square, normal);
        handleHeaterEffects(circle, square);
    }
}

void PhysicsEngine::resolveSquareCircle (Core::GameObject& square, Core::GameObject& circle) {
    Math::Vector2D r_pos = square.pos();
    Math::Vector2D r_size = square.size();
    Math::Vector2D c_pos = circle.pos();
    float radius = circle.radius();

    float closest_x = std::clamp(c_pos.x(), r_pos.x(), r_pos.x() + r_size.x());
    float closest_y = std::clamp(c_pos.y(), r_pos.y(), r_pos.y() + r_size.y());

    float distance_x = c_pos.x() - closest_x;
    float distance_y = c_pos.y() - closest_y;
    float distance = std::sqrt(distance_x * distance_x + distance_y * distance_y);

    if (distance < radius) {
        Math::Vector2D normal {0.0f, 0.0f};
        float overlap = 0.0f;

        if (std::abs(distance) < 1e-5f) {
            float center_x = r_pos.x() + r_size.x() * 0.5f;
            normal = (c_pos.x() > center_x) ? Math::Vector2D { 1.0f, 0.0f } : Math::Vector2D{ -1.0f, 0.0f };
            overlap = radius;
        } else {
            normal = { distance_x / distance, distance_y / distance };
            overlap = radius - distance;
        }

        square.setPosition(r_pos - normal * (overlap * 0.5f));
        circle.setPosition(c_pos + normal * (overlap * 0.5f));

        applyImpulse(square, circle, normal);
        handleHeaterEffects(square, circle);
    }
}

void PhysicsEngine::resolveSquareSquare (Core::GameObject& square1, Core::GameObject& square2) {
    Math::Vector2D pos1 = square1.pos();
    Math::Vector2D pos2 = square2.pos();
    Math::Vector2D size1 = square1.size();
    Math::Vector2D size2 = square2.size();

    float center_x1 = pos1.x() + size1.x() * 0.5f;
    float center_y1 = pos1.y() + size1.y() * 0.5f;
    float center_x2 = pos2.x() + size2.x() * 0.5f;
    float center_y2 = pos2.y() + size2.y() * 0.5f;

    float delta_x = center_x2 - center_x1;
    float delta_y = center_y2 - center_y1;

    float min_dist_x = (size1.x() + size2.x()) * 0.5f;
    float min_dist_y = (size1.y() + size2.y()) * 0.5f;

    float overlap_x = min_dist_x - std::abs(delta_x);
    float overlap_y = min_dist_y - std::abs(delta_y);

    if (overlap_x > 0.0f && overlap_y > 0.0f) {
        Math::Vector2D normal{0.0f, 0.0f};

        if (overlap_x < overlap_y) {
            normal = { (delta_x > 0.0f) ? 1.0f : -1.0f, 0.0f };
            square1.setPosition({ pos1.x() - normal.x() * overlap_x * 0.5f, pos1.y() });
            square2.setPosition({ pos2.x() + normal.x() * overlap_x * 0.5f, pos2.y() });
        } else {
            normal = { 0.0f, (delta_y > 0.0f) ? 1.0f : -1.0f };
            square1.setPosition({ pos1.x(), pos1.y() - normal.y() * overlap_y * 0.5f });
            square2.setPosition({ pos2.x(), pos2.y() + normal.y() * overlap_y * 0.5f });
        }

        applyImpulse(square1, square2, normal);
        handleHeaterEffects(square1, square2);
    }
}

void PhysicsEngine::collideWithWalls (std::vector<std::unique_ptr<GameObject>>& objects, 
                                     float x_min, float x_max, float y_min, float y_max) {
    for (auto& obj : objects) {
        if (!obj || !obj->isEnabled()) continue;

        if (obj->getHitboxType() == HitboxType::Circle) {            
            Math::Vector2D pos = obj->pos();
            Math::Vector2D vel = obj->velocity();
            float r = obj->radius();

            if (pos.x() - r < x_min) {
                obj->setPosition({ x_min + r, pos.y() });
                obj->setVelocity({ -vel.x(), vel.y() });
            }
            else if (pos.x() + r > x_max) {
                obj->setPosition({ x_max - r, pos.y() });
                obj->setVelocity({ -vel.x(), vel.y() });
            }

            if (pos.y() - r < y_min) {
                obj->setPosition({ pos.x(), y_min + r });
                obj->setVelocity({ vel.x(), -vel.y() });
            }
            else if (pos.y() + r > y_max) {
                obj->setPosition({ pos.x(), y_max - r });
                obj->setVelocity({ vel.x(), -vel.y() });
            }
        }

        else if (obj->getHitboxType() == HitboxType::Rectangle) {            
            Math::Vector2D pos = obj->pos();
            Math::Vector2D vel = obj->velocity();
            Math::Vector2D size = obj->size();

            if (pos.x() < x_min) {
                obj->setPosition({ x_min, pos.y() });
                obj->setVelocity({ -vel.x(), vel.y() });
            }
            else if (pos.x() + size.x() > x_max) {
                obj->setPosition({ x_max - size.x(), pos.y() });
                obj->setVelocity({ -vel.x(), vel.y() });
            }

            if (pos.y() < y_min) {
                obj->setPosition({ pos.x(), y_min });
                obj->setVelocity({ vel.x(), -vel.y() });
            }
            else if (pos.y() + size.y() > y_max) {
                obj->setPosition({ pos.x(), y_max - size.y() });
                obj->setVelocity({ vel.x(), -vel.y() });
            }
        }
    }
}

} // namespace Core