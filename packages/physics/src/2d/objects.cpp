#include <cassert>
#include <cmath>
#include "physics/2d/shapes.h"
#include "physics/2d/objects.h"


namespace Physics {
    Object::Object() : body(std::make_unique<Circle>(Vec2D(0,0), 1.0f)), mass(0.0f) {}
    Object::Object(std::unique_ptr<Shape> body, float mass) : body(std::move(body)), mass(mass) {}
}