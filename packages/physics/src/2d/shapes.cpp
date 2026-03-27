#include <cassert>
#include <cmath>
#include "physics/2d/shapes.h"


namespace Physics {
    Vec2D::Vec2D(float x, float y) : x(x), y(y) {}

    void Shape::translate(float dx, float dy) {
        center.x += dx;
        center.y += dy;

        if (!points.empty()) {
            for (auto& p : points) {
                p.x += dx;
                p.y += dy;
            }
        }
    }

    Circle::Circle(Physics::Vec2D center, float radius) : center(center), radius(radius) {}
    void Circle::rotate(float radians) {}
    void Circle::rotate(float radians, Physics::Vec2D axis) {
        float cosA = std::cos(radians);
        float sinA = std::sin(radians);   
        float cx = center.x - axis.x;
        float cy = center.y - axis.y;

        center.x = (cx * cosA - cy * sinA) + axis.x;
        center.y = (cx * sinA + cy * cosA) + axis.y;        
    }

    RegularPolygon::RegularPolygon() : center(Physics::Vec2D()), sides(3), radius(10.0f), yaw(0.0f) {};
    RegularPolygon::RegularPolygon(Physics::Vec2D center, int sides, float radius, float yaw) : center(center), sides(sides), radius(radius), yaw(yaw) {
        assert(sides >= 3 && "Polygon creation failed: sides must be >= 3");

        points.reserve(sides);

        float arclength = (2.0f*M_PI)/sides;

        for (int i = 0; i < sides; ++i) {
            float angle = yaw + i * (2.0f * M_PI / sides);
            float vx = center.x + radius * std::cos(angle);
            float vy = center.y + radius * std::sin(angle);

            points.emplace_back(vx, vy);
        }

    }
    void RegularPolygon::rotate(float radians) {
        rotate(radians, this->center);
    }
    void RegularPolygon::rotate(float radians, Physics::Vec2D axis) {
        float cosA = std::cos(radians);
        float sinA = std::sin(radians);

        for (auto& p : points) {
            float tx = p.x - axis.x;
            float ty = p.y - axis.y;

            float rx = tx * cosA - ty * sinA;
            float ry = tx * sinA + ty * cosA;

            p.x = rx + axis.x;
            p.y = ry + axis.y;
        }

        if (&axis != &this->center) {
                float cx = center.x - axis.x;
                float cy = center.y - axis.y;
                center.x = (cx * cosA - cy * sinA) + axis.x;
                center.y = (cx * sinA + cy * cosA) + axis.y;
            }
    }
}