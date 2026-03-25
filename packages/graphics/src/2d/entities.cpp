#include <cassert>
#include <cmath>
#include "graphics/colors.h"
#include "physics/2d/shapes.h"
#include "physics/2d/objects.h"
#include "graphics/2d/entities.h"


namespace Graphics {
    Entity::Entity(Physics::Object object, Graphics::Color color) : object(object), color(color) {}
}