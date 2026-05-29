#include <cassert>
#include <cmath>
#include "physics/2d/geom.h"
#include "physics/2d/objects.h"


namespace Physics {
    Object::Object() : body(Physics::Circle(Vec2D(0,0), 1.0f)), mass(0.0f) {}
    Object::Object(Physics::Circle body, float mass) : body(std::move(body)), mass(mass) {}
    Object::Object(Physics::RegularPolygon body, float mass) : body(std::move(body)), mass(mass) {}
    Object::Object(Physics::CustomPolygon body, float mass) : body(std::move(body)), mass(mass) {}
    void Object::processPhysics() {
        velocity.x += acceleration.x;
        velocity.y += acceleration.y;
        dTheta += ddTheta;
        std::visit([this](auto& shape) {
                shape.translate(this->velocity.x, this->velocity.y);
            }, 
            this->body
        );
        std::visit([this](auto& shape) {
            shape.rotate(this->dTheta);
            }, 
            this->body
        );
    }
    void Object::setAcceleration(Vec2D newAcceleration) {
        acceleration = newAcceleration;
    }
    void Object::setVelocity(Vec2D newVelocity) {
        velocity = newVelocity;
    }
    void Object::setDDTheta(float newDDTheta) {
        ddTheta = newDDTheta;
    }
    void Object::setDTheta(float newDTheta) {
        dTheta = newDTheta;
    }
}