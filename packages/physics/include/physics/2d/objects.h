#pragma once
#include <variant>
#include <vector>
#include "physics/2d/shapes.h"

namespace Physics {
    class Object {
        public:
            Object();
            Object(RegularPolygon body, float mass);
            RegularPolygon body;
        private:
            float mass;
            Vec2D velocity;
            Vec2D acceleration;
            float dTheta;
            float ddTheta;
    };
}