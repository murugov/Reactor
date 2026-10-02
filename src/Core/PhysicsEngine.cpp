#include <cmath>
#include <algorithm>
#include "Core/GameObject.hpp"
#include "Gameplay/Heater.hpp"
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

static void handleHeaterEffects(Core::GameObject& obj1, Core::GameObject& obj2) {
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
    
void PhysicsEngine::collideObjects (std::vector<std::unique_ptr<GameObject>>& objects) {
    for (size_t i = 0; i < objects.size(); ++i) {
        GameObject* obj1 = objects[i].get();
        if (!obj1 || !obj1->isEnabled()) continue;

        for (size_t j = i + 1; j < objects.size(); ++j) {
            GameObject* obj2 = objects[j].get();
            if (!obj2 || !obj2->isEnabled()) continue;

            auto type1 = obj1->getHitboxType();
            auto type2 = obj2->getHitboxType();

            if (type1 == HitboxType::Circle && type2 == HitboxType::Circle) {
                resolveCircleCircle(*obj1, *obj2);
            }
            else if (type1 == HitboxType::Rectangle && type2 == HitboxType::Rectangle) {
                resolveSquareSquare(*obj1, *obj2);
            }
            else if (type1 == HitboxType::Rectangle && type2 == HitboxType::Circle) {
                resolveSquareCircle(*obj1, *obj2);
            }
            else if (type1 == HitboxType::Circle && type2 == HitboxType::Rectangle) {
                resolveSquareCircle(*obj2, *obj1);
            }
        }
    }
}

void PhysicsEngine::resolveCircleCircle (Core::GameObject& obj1, Core::GameObject& obj2) {
    Math::Vector2D pos1 = obj1.pos();
    Math::Vector2D pos2 = obj2.pos();
    float r1 = obj1.radius();
    float r2 = obj2.radius();

    Math::Vector2D delta = pos2 - pos1;
    float distance = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());
    float min_dist = r1 + r2;

    if (distance < min_dist && distance > 0.0f) {
        float overlap = min_dist - distance;
        Math::Vector2D normal = delta * (1.0f / distance);
        
        obj1.setPosition(pos1 - normal * (overlap * 0.5f));
        obj2.setPosition(pos2 + normal * (overlap * 0.5f));

        applyImpulse(obj1, obj2, normal);
        handleHeaterEffects(obj1, obj2);
    }
}

void PhysicsEngine::resolveSquareSquare (Core::GameObject& obj1, Core::GameObject& obj2) {
    Math::Vector2D pos1 = obj1.pos();
    Math::Vector2D pos2 = obj2.pos();
    Math::Vector2D size1 = obj1.size();
    Math::Vector2D size2 = obj2.size();

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
            obj1.setPosition({ pos1.x() - normal.x() * overlap_x * 0.5f, pos1.y() });
            obj2.setPosition({ pos2.x() + normal.x() * overlap_x * 0.5f, pos2.y() });
        } else {
            normal = { 0.0f, (delta_y > 0.0f) ? 1.0f : -1.0f };
            obj1.setPosition({ pos1.x(), pos1.y() - normal.y() * overlap_y * 0.5f });
            obj2.setPosition({ pos2.x(), pos2.y() + normal.y() * overlap_y * 0.5f });
        }

        applyImpulse(obj1, obj2, normal);
        handleHeaterEffects(obj1, obj2);
    }
}

void PhysicsEngine::resolveSquareCircle (Core::GameObject& obj1, Core::GameObject& obj2) {
    Math::Vector2D r_pos = obj1.pos();
    Math::Vector2D r_size = obj1.size();
    Math::Vector2D c_pos = obj2.pos();
    float radius = obj2.radius();

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

        obj1.setPosition(r_pos - normal * (overlap * 0.5f));
        obj2.setPosition(c_pos + normal * (overlap * 0.5f));

        applyImpulse(obj1, obj2, normal);
        handleHeaterEffects(obj1, obj2);
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