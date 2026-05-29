#pragma once
#include <variant>
#include <vector>
#include "physics/2d/geom.h"

namespace Physics {
    using BodyVariant = std::variant<Circle, RegularPolygon, CustomPolygon>;

    class Object {
        public:
            Object();
            Object(Physics::Circle body, float mass = 0);
            Object(Physics::RegularPolygon body, float mass = 0);
            Object(Physics::CustomPolygon body, float mass = 0);
            BodyVariant body;
            Vec2D acceleration = Vec2D(0.0f, 0.0f);
            void processPhysics();
            void setAcceleration(Vec2D newAcceleration);
            void setVelocity(Vec2D newVelocity);
            void setDDTheta(float newDDTheta);
            void setDTheta(float newDTheta);
        private:
            float mass;
            Vec2D velocity = Vec2D(0.0f, 0.0f);
            float dTheta = 0.0f;
            float ddTheta = 0.0f;
    };
}