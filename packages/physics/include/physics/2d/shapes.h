#pragma once
#include <vector>

namespace Physics {
    struct Vec2D {
        float x,y;
        Vec2D ();
        Vec2D (float x, float y);
    };
    class Circle {
        public:
            Circle (Physics::Vec2D center, float radius);
            Physics::Vec2D center;
            float radius;
        private:
            void translate(float dx, float dy);
            void rotate(float radians);
            void rotate(float radians, Physics::Vec2D axis);
    };
    class RegularPolygon {
        public:
            RegularPolygon();
            RegularPolygon (Physics::Vec2D center, int sides, float radius, float yaw);
            int sides;
            std::vector<Physics::Vec2D> points;
        private:
            Physics::Vec2D center;
            float radius;
            float yaw;
            float arclength;
            void translate(float dx, float dy);
            void rotate(float degrees);
            void rotate(float radians, Physics::Vec2D axis);
    };
}