#include <cassert>
#include <cmath>
#include "physics/2d/shapes.h"
#include "physics/2d/objects.h"


namespace Physics {
    Object::Object() : body(RegularPolygon()), mass(0.0f) {}
    Object::Object(RegularPolygon body, float mass) : body(body), mass(mass) {}
}