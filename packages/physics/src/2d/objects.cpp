#include <cassert>
#include <cmath>
#include "physics/2d/geom.h"
#include "physics/2d/objects.h"


namespace Physics {
    Object::Object() : body(Physics::Circle(Vec2D(0,0), 1.0f)), mass(0.0f) {}
    Object::Object(Physics::Circle body, float mass) : body(std::move(body)), mass(mass) {}
    Object::Object(Physics::RegularPolygon body, float mass) : body(std::move(body)), mass(mass) {}
}