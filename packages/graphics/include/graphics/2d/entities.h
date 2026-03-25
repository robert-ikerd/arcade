#pragma once
#include <SDL3/SDL.h>
#include <physics/2d/objects.h>
#include <graphics/colors.h>


namespace Graphics {
    class Entity {
        public:
            Entity(Physics::Object object, Graphics::Color color);
        private:
            Physics::Object object;
            Graphics::Color color;
            float borderWidth;
    };
}