#pragma once
#include <vector>

namespace Physics {
    struct Vec2D {
        float x,y;
        Vec2D (float x=0.0f, float y=0.0f);
    };
    class Shape {
        public:
            virtual ~Shape() {}
            Vec2D center;
            float radius;
            std::vector<Vec2D> points;
            void translate(float dx, float dy);
    };
    class Circle : public Shape {
        public:
            Circle (Vec2D center, float radius);
            Vec2D center;
            float radius;
        private:
            void rotate(float radians);
            void rotate(float radians, Vec2D axis);
    };
    class RegularPolygon : public Shape {
        public:
            RegularPolygon();
            RegularPolygon (Vec2D center, int sides, float radius, float yaw);
            int sides;
            std::vector<Vec2D> points;
        private:
            Vec2D center;
            float radius;
            float yaw;
            float arclength;
            void rotate(float degrees);
            void rotate(float radians, Vec2D axis);
    };
}