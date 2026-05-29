#pragma once
#include <vector>

namespace Physics {
    float degreesToRadians(float degrees);
    float radiansToDegrees(float radians);
    double wrapAngle(float radians);
    struct Vec2D {
        float x,y;
        Vec2D (float x=0.0f, float y=0.0f);
    };
    class Circle {
        public:
            Circle (Vec2D center, float radius);
            Vec2D center;
            float radius;
            void translate(float dx, float dy);
            void rotate(float radians);
            void rotate(float radians, Vec2D axis);
            float yaw;
    };
    class RegularPolygon {
        public:
            RegularPolygon();
            RegularPolygon (Vec2D center, int sides, float radius, float yaw = 0);
            int sides;
            std::vector<Vec2D> points;
            void translate(float dx, float dy);
            void rotate(float radians);
            void rotate(float radians, Vec2D axis);
            float yaw;
        private:
            Vec2D center;
            float radius;
            float arclength;
    };
    class CustomPolygon {
        public:
            CustomPolygon (Vec2D center, std::vector<Vec2D> points, float yaw = 0);
            std::vector<Vec2D> points;
            float yaw;
            void translate(float dx, float dy);
            void rotate(float radians);
            void rotate(float radians, Vec2D axis);
        private:
            Vec2D center;
    };
}