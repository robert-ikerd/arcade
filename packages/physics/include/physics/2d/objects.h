#pragma once
#include <variant>
#include <vector>
#include "physics/2d/geom.h"

namespace Physics {
    using BodyVariant = std::variant<Circle, RegularPolygon>;

    class Object {
        public:
            Object();
            Object(Physics::Circle body, float mass = 0);
            Object(Physics::RegularPolygon body, float mass = 0);
            BodyVariant body;
        private:
            float mass;
            Vec2D velocity;
            Vec2D acceleration;
            float dTheta;
            float ddTheta;
    };
}